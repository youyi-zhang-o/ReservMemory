#include <cstddef>
#include <google/protobuf/message.h>
#include <memory>
#include "IRsvMemUsr.h"
#include "pub_def.h"
#include "IRsvMemUpgradeAdaptor.h"

class IRsvMemMng {
public:
    virtual ~IRsvMemMng() = default;
    virtual bool Initialize(uint8_t* base, size_t size) = 0;
    virtual void RegUpgradeAdaptorCreateFunc(RsvMemUpgradeAdaptorCreateFunc&&) = 0;
    virtual RsvMemErrCode RegUsrCreateFunc(UsrId id, RsvMemUsrCreateFunc&& createFunc) = 0;
    virtual std::shared_ptr<IRsvMemUsr> GetUsr(UsrId id) = 0;
    virtual RsvMemErrCode RegRawBufferUsr(UsrId id, size_t len) = 0;
    virtual RsvMemErrCode GetRawBuffer(UsrId, RawBuffer& buffer) = 0;
    // 确保所有需要升级的 User 注册完之后调用 调用这个接口之后 保留内存空间将被新框架接管
    // 对于没有历史遗留问题的新开发设备 初始化时调用 UpgradeAdator 判断保留内存无效后 直接开始使用保留内存 可以不必调用这个接口
    virtual RsvMemErrCode Upgrade() = 0;
    // 包加载、包匹配结束时通知保留内存管理模块 设备启动时判断是否处于包加载状态
    // 如果是包加载激活启动 对保留内存的写操作将被缓存
    // 等到通知包加载结束后放开对保留内存的写操作 将之前所有缓存的内容刷新到保留内存
    virtual bool NotifySwdlEnd() = 0;
    // 系统关闭通知 如主动复位 单板对象析构 异常复位等；将触发将脏数据写到保留内存
    virtual void OnSystemClose() = 0;
};
