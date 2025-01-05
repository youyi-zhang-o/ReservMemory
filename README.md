
# 1. Logical View（逻辑视图）

```mermaid
classDiagram
    class IDeviceUpgradeStatus {
        <<interface>>
        +IsUpgrading() : bool
    }

    class DeviceUpgradeStatus {
        -m_upgrading : bool
        +SetUpgrading(u : bool) : void
        +IsUpgrading() : bool
    }

    IDeviceUpgradeStatus <|-- DeviceUpgradeStatus

    class ReserveMemoryManager {
        -m_header : MemoryHeader
        -m_base : uint8_t*
        -m_size : size_t
        -m_upgradeStatus : IDeviceUpgradeStatus*
        -m_pendingWrites : vector<PendingWrite>
        --
        +Initialize(base : uint8_t*, size : size_t) : bool
        +SetUpgradeStatusChecker(checker : IDeviceUpgradeStatus*) : void
        +SaveData(configId : uint32_t, msg : google::protobuf::Message&) : bool
        +SaveData(configId : uint32_t, data : vector<uint8_t>) : bool
        +LoadData(configId : uint32_t, msg : google::protobuf::Message&) : bool
        +LoadData(configId : uint32_t, data : vector<uint8_t>&) : bool
        +LoadData(configId : uint32_t, outPtr : uint8_t*&, outSize : size_t&) : bool
        +FinishUpgrade() : void
        +CancelUpgrade() : void
        --
        -CommitWrite(configId : uint32_t, data : vector<uint8_t>) : bool
        -FindBlockIndex(ownerId : uint32_t) : int
        -AllocateOrExpandBlock(ownerId : uint32_t, neededSize : size_t) : int
        -AutoAllocateBlock(ownerId : uint32_t, neededSize : size_t) : int
        -ExpandBlockIfNeeded(index : int, neededSize : size_t) : bool
        -CompactMemory() : void
        -LoadHeader() : void
        -SaveHeader() : void
    }

    class MemoryHeader {
        +version : uint32_t
        +allocatedBlocks : uint32_t
        +blocks : BlockInfo[256]
    }
    class BlockInfo {
        +ownerId : uint32_t
        +startOffset : uint32_t
        +usedSize : uint32_t
        +capacity : uint32_t
    }

    class PendingWrite {
        +configId : uint32_t
        +type : WriteType
        +rawData : vector<uint8_t>
    }

    class WriteType{
        <<enumeration>>
        Proto
        RawVector
    }

    ReserveMemoryManager o-- MemoryHeader : has
    MemoryHeader o-- BlockInfo : includes
    ReserveMemoryManager o-- PendingWrite : caches
    PendingWrite o-- WriteType
    ReserveMemoryManager --> IDeviceUpgradeStatus : "uses"

    note for ReserveMemoryManager "核心逻辑类，提供写操作缓存/commit等功能"
    note for DeviceUpgradeStatus "简单实现，内部用bool标记升级状态"
```

逻辑要点：
	•	IDeviceUpgradeStatus：定义 IsUpgrading() 接口；
	•	DeviceUpgradeStatus：实现上述接口，并提供 SetUpgrading(bool)；
	•	ReserveMemoryManager：是核心，持有一个 IDeviceUpgradeStatus* 用于判断是否升级中；在写操作时如升级中则缓存到 m_pendingWrites，否则直接CommitWrite。
	•	MemoryHeader / BlockInfo：存储在保留内存起始，用于记录各个块分配信息；
	•	PendingWrite：缓存的写操作（Protobuf 序列化后或原始向量），区分类型（Proto / RawVector）。

# 2. Development View（开发视图）

开发视图侧重项目的代码组织、包/模块划分，以及如何在工程结构中分配各类、接口、库的依赖等。可以用 UML 包图 或 组件图 表示。
```mermaid
flowchart TB
    A[include/\nheaders] -->|IDeviceUpgradeStatus.h, DeviceUpgradeStatus.h\nReserveMemoryManager.h, ...| B
    B[core/\nlogic] --> |ReserveMemoryManager.cpp| C
    B --> |DeviceUpgradeStatus.cpp| C
    C[lib/\nprotobuf] --> D[executable]
    B --> D
    A --> D

    subgraph "Project Repo"
    A(Include Folder)
    B(Src Folder)
    end

    style A fill:#CCEEFF,stroke:#3399FF,stroke-width:1px
    style B fill:#CCEEFF,stroke:#3399FF,stroke-width:1px
    style C fill:#FFEECC,stroke:#FF9933,stroke-width:1px
    style D fill:#CCFFCC,stroke:#33AA33,stroke-width:1px
```
	•	include/headers：存放 .h 文件，如 IDeviceUpgradeStatus.h, DeviceUpgradeStatus.h, ReserveMemoryManager.h。
	•	core/logic：存放 .cpp 文件，如 ReserveMemoryManager.cpp, DeviceUpgradeStatus.cpp。
	•	依赖**protobuf** 库进行序列化/反序列化；
	•	编译后生成 executable 或静态/动态库。

# 3. Process View（过程视图）

过程视图重点关注系统运行时的并发、线程、交互流程等。由于我们示例工程主要是单线程演示，可以用活动图或顺序图说明写操作或升级流程。

这里给出一个活动图，示例展示 “SaveData 被调用时” 的决策与操作流程：

## 3.1 UML 活动图：SaveData 调用流程
```mermaid
flowchart TD
    A("调用 SaveData(configId, data)") --> B{"IsUpgrading()?"}
    B -- yes --> C("将写操作封装为\nPendingWrite{configId, rawData}\n推入 m_pendingWrites")
    C --> E("返回 true (写操作缓存成功)")
    B -- no --> D("CommitWrite(configId, data)")
    D --> E("返回 写入成功或失败")
```
	•	IsUpgrading()：由 ReserveMemoryManager::m_upgradeStatus 提供
	•	如果是升级中，则缓存到 m_pendingWrites；否则直接调用 CommitWrite（进行分配/扩容/写入）。

线程或并发
	•	如果系统需要多线程并发访问 ReserveMemoryManager，需在入口（SaveData(), FinishUpgrade(), CancelUpgrade(), LoadData()等）或内部加锁（互斥）。
	•	本示例未体现多线程，可在此视图中标注 “此处需加全局互斥锁” 或 “此处需使用读写锁” 等细节。

# 4. Physical View（物理视图）
```mermaid
graph LR
    subgraph Embedded_Device
        nodeMem((Flash or RAM)) -- "Persist" --> ReserveMemoryManager
        ReserveMemoryManager -- "Check" --> IDeviceUpgradeStatus
        ReserveMemoryManager -- "Link" --> ProtobufRuntime
        IDeviceUpgradeStatus --> DeviceUpgradeStatus
    end
```

# 5. Scenarios（场景视图）
```mermaid
sequenceDiagram
    participant Main
    participant DeviceUpgradeStatus
    participant ReserveMemoryManager
    participant PendingWrites
    participant Memory

    Main->>DeviceUpgradeStatus: SetUpgrading(true)
    Main->>ReserveMemoryManager: SaveData(10, "Bob/99" [Protobuf])
    ReserveMemoryManager->>DeviceUpgradeStatus: IsUpgrading()
    DeviceUpgradeStatus-->>ReserveMemoryManager: return true
    ReserveMemoryManager->>PendingWrites: push_back({10, Proto, rawData="Bob/99"})
    Main->>ReserveMemoryManager: SaveData(20, [1,2,3,4,5] [RawVector])
    ReserveMemoryManager->>DeviceUpgradeStatus: IsUpgrading()
    DeviceUpgradeStatus-->>ReserveMemoryManager: return true
    ReserveMemoryManager->>PendingWrites: push_back({20, RawVector, [1,2,3,4,5]})

    Main->>ReserveMemoryManager: FinishUpgrade()
    ReserveMemoryManager->>PendingWrites: foreach pending
    ReserveMemoryManager->>ReserveMemoryManager: CommitWrite(configId, data)
    ReserveMemoryManager->>Memory: allocate/expand + memmove if needed
    ReserveMemoryManager->>Memory: memcpy data
    loop for each pending
        ReserveMemoryManager->>ReserveMemoryManager: SaveHeader()
    end
    PendingWrites-->>ReserveMemoryManager: all committed
    ReserveMemoryManager->>PendingWrites: clear()

    Main->>DeviceUpgradeStatus: SetUpgrading(false)
```