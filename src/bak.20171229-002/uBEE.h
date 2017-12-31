#ifndef UGG_UGG_H
#define UGG_UGG_H

namespace uBEE
{
typedef enum MdMode {
    Md_Null        = 1,  // 不接收行情流
    Md_Real        = 2,  //实时行情
    Md_Simulation  = 3,  // 接收模拟行情
    Md_Backtest    = 4   // 接收回放行情
}MdMode;


struct Block : public Md, public Td {

    using Md::onTick;
    using Md::onBar;

	using Md::getTicks;
	using Md::getBars;
    using Md::getInstruments

    using Td::BuyOpen;
    using Td::BuyClose;
    using Td::SellOpen;
    using Td::SellClose;
    using Td::CancelOrder;

    using Td::reqQryTransferBank;
    using Td::reqQrySettlementInfo;

} // end struct Block

} // end namespace uBEE


#endif // UGG_UGG_H
