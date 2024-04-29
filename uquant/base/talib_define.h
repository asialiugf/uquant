namespace uBEE {
#define MA_T static MA_t
#define RSV_T static RSV_t
#define EMA_T static EMA_t
#define SMA_T static SMA_t
#define SERIAL_T static FutureSerial
#define BOOL_T static bool
// 要判断 obj是否存在  是否为 序列
#define PLOT(obj, aa) obj.plot(#obj, aa)
} // namespace uBEE