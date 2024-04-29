#include "ctp_traderApi.h"

#include <stdio.h>

namespace uBEE {

CThostFtdcTraderApi *CTraderApi::CreateFtdcTraderApi(const char *pszFlowPath /*= ""*/) {
    return m_pApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);
}

const char *CTraderApi::GetApiVersion() { return m_pApi->GetApiVersion(); }

//////////////////////////////////////////////////////////////////////////以下可替换模板

void CTraderApi::Release() {
    printf("<Release>\n");
    printf("</Release>\n");

    m_pApi->Release();
};

void CTraderApi::Init() {
    printf("<Init>\n");
    printf("</Init>\n");

    m_pApi->Init();
};

int CTraderApi::Join() {
    printf("<Join>\n");
    printf("</Join>\n");

    return m_pApi->Join();
};
const char *CTraderApi::GetTradingDay() {
    printf("<GetTradingDay>\n");
    printf("</GetTradingDay>\n");

    return m_pApi->GetTradingDay();
};

void CTraderApi::RegisterFront(char *pszFrontAddress) {
    printf("<RegisterFront>\n");
    printf("\tpszFrontAddress [%s]\n", pszFrontAddress);
    printf("</RegisterFront>\n");

    m_pApi->RegisterFront(pszFrontAddress);
}

void CTraderApi::RegisterNameServer(char *pszNsAddress) {
    printf("<RegisterNameServer>\n");
    printf("\tpszNsAddress [%s]\n", pszNsAddress);
    printf("</RegisterNameServer>\n");

    m_pApi->RegisterNameServer(pszNsAddress);
}

void CTraderApi::RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo) {
    printf("<RegisterFensUserInfo>\n");
    if (pFensUserInfo) {
        printf("\tBrokerID [%s]\n", pFensUserInfo->BrokerID);
        printf("\tUserID [%s]\n", pFensUserInfo->UserID);
        printf("\tLoginMode [%c]\n", pFensUserInfo->LoginMode);
    }
    printf("</RegisterFensUserInfo>\n");

    m_pApi->RegisterFensUserInfo(pFensUserInfo);
};

void CTraderApi::RegisterSpi(CThostFtdcTraderSpi *pSpi) {
    printf("<RegisterSpi>\n");
    if (pSpi) {
    }
    printf("</RegisterSpi>\n");

    m_pApi->RegisterSpi(pSpi);
};

void CTraderApi::SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType) {
    printf("<SubscribePrivateTopic>\n");
    printf("\tnResumeType [%d]\n", nResumeType);
    printf("</SubscribePrivateTopic>\n");

    m_pApi->SubscribePrivateTopic(nResumeType);
}

void CTraderApi::SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType) {
    printf("<SubscribePublicTopic>\n");
    printf("\tnResumeType [%d]\n", nResumeType);
    printf("</SubscribePublicTopic>\n");

    m_pApi->SubscribePublicTopic(nResumeType);
}

int CTraderApi::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID) {
    printf("\n<ReqAuthenticate>\n");
    if (pReqAuthenticateField) {
        printf("\tBrokerID [%s]\n", pReqAuthenticateField->BrokerID);
        printf("\tUserID [%s]\n", pReqAuthenticateField->UserID);
        printf("\tAuthCode [%s]\n", pReqAuthenticateField->AuthCode);
        printf("\tAppID [%s]\n", pReqAuthenticateField->AppID);
        printf("\tUserProductInfo [%s]\n", pReqAuthenticateField->UserProductInfo);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqAuthenticate>\n\n");

    return m_pApi->ReqAuthenticate(pReqAuthenticateField, nRequestID);
};

int CTraderApi::RegisterUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo) {
    printf("<RegisterUserSystemInfo>\n");
    if (pUserSystemInfo) {
        printf("\tBrokerID [%s]\n", pUserSystemInfo->BrokerID);
        printf("\tUserID [%s]\n", pUserSystemInfo->UserID);
        printf("\tClientSystemInfo [%s]\n", pUserSystemInfo->ClientSystemInfo);
        printf("\treserve1 [%s]\n", pUserSystemInfo->reserve1);
        printf("\tClientLoginTime [%s]\n", pUserSystemInfo->ClientLoginTime);
        printf("\tClientAppID [%s]\n", pUserSystemInfo->ClientAppID);
        printf("\tClientPublicIP [%s]\n", pUserSystemInfo->ClientPublicIP);
        printf("\tClientLoginRemark [%s]\n", pUserSystemInfo->ClientLoginRemark);
        printf("\tClientSystemInfoLen [%d]\n", pUserSystemInfo->ClientSystemInfoLen);
        printf("\tClientIPPort [%d]\n", pUserSystemInfo->ClientIPPort);
    }
    printf("</RegisterUserSystemInfo>\n");

    return m_pApi->RegisterUserSystemInfo(pUserSystemInfo);
};

int CTraderApi::SubmitUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo) {
    printf("<SubmitUserSystemInfo>\n");
    if (pUserSystemInfo) {
        printf("\tBrokerID [%s]\n", pUserSystemInfo->BrokerID);
        printf("\tUserID [%s]\n", pUserSystemInfo->UserID);
        printf("\tClientSystemInfo [%s]\n", pUserSystemInfo->ClientSystemInfo);
        printf("\treserve1 [%s]\n", pUserSystemInfo->reserve1);
        printf("\tClientLoginTime [%s]\n", pUserSystemInfo->ClientLoginTime);
        printf("\tClientAppID [%s]\n", pUserSystemInfo->ClientAppID);
        printf("\tClientPublicIP [%s]\n", pUserSystemInfo->ClientPublicIP);
        printf("\tClientLoginRemark [%s]\n", pUserSystemInfo->ClientLoginRemark);
        printf("\tClientSystemInfoLen [%d]\n", pUserSystemInfo->ClientSystemInfoLen);
        printf("\tClientIPPort [%d]\n", pUserSystemInfo->ClientIPPort);
    }
    printf("</SubmitUserSystemInfo>\n");

    return m_pApi->SubmitUserSystemInfo(pUserSystemInfo);
};

int CTraderApi::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) {
    printf("<ReqUserLogin>\n");
    if (pReqUserLoginField) {
        printf("\tTradingDay [%s]\n", pReqUserLoginField->TradingDay);
        printf("\tBrokerID [%s]\n", pReqUserLoginField->BrokerID);
        printf("\tUserID [%s]\n", pReqUserLoginField->UserID);
        printf("\tPassword [%s]\n", pReqUserLoginField->Password);
        printf("\tUserProductInfo [%s]\n", pReqUserLoginField->UserProductInfo);
        printf("\tInterfaceProductInfo [%s]\n", pReqUserLoginField->InterfaceProductInfo);
        printf("\tProtocolInfo [%s]\n", pReqUserLoginField->ProtocolInfo);
        printf("\tMacAddress [%s]\n", pReqUserLoginField->MacAddress);
        printf("\tOneTimePassword [%s]\n", pReqUserLoginField->OneTimePassword);
        printf("\treserve1 [%s]\n", pReqUserLoginField->reserve1);
        printf("\tLoginRemark [%s]\n", pReqUserLoginField->LoginRemark);
        printf("\tClientIPAddress [%s]\n", pReqUserLoginField->ClientIPAddress);
        printf("\tClientIPPort [%d]\n", pReqUserLoginField->ClientIPPort);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqUserLogin>\n");

    return m_pApi->ReqUserLogin(pReqUserLoginField, nRequestID);
};

int CTraderApi::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) {
    printf("<ReqUserLogout>\n");
    if (pUserLogout) {
        printf("\tBrokerID [%s]\n", pUserLogout->BrokerID);
        printf("\tUserID [%s]\n", pUserLogout->UserID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqUserLogout>\n");

    return m_pApi->ReqUserLogout(pUserLogout, nRequestID);
};

int CTraderApi::ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) {
    printf("<ReqUserPasswordUpdate>\n");
    if (pUserPasswordUpdate) {
        printf("\tBrokerID [%s]\n", pUserPasswordUpdate->BrokerID);
        printf("\tUserID [%s]\n", pUserPasswordUpdate->UserID);
        printf("\tOldPassword [%s]\n", pUserPasswordUpdate->OldPassword);
        printf("\tNewPassword [%s]\n", pUserPasswordUpdate->NewPassword);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqUserPasswordUpdate>\n");

    return m_pApi->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
};

int CTraderApi::ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate,
                                                int nRequestID) {
    printf("<ReqTradingAccountPasswordUpdate>\n");
    if (pTradingAccountPasswordUpdate) {
        printf("\tBrokerID [%s]\n", pTradingAccountPasswordUpdate->BrokerID);
        printf("\tAccountID [%s]\n", pTradingAccountPasswordUpdate->AccountID);
        printf("\tOldPassword [%s]\n", pTradingAccountPasswordUpdate->OldPassword);
        printf("\tNewPassword [%s]\n", pTradingAccountPasswordUpdate->NewPassword);
        printf("\tCurrencyID [%s]\n", pTradingAccountPasswordUpdate->CurrencyID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqTradingAccountPasswordUpdate>\n");

    return m_pApi->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, nRequestID);
};

int CTraderApi::ReqUserAuthMethod(CThostFtdcReqUserAuthMethodField *pReqUserAuthMethod, int nRequestID) {
    printf("<ReqUserAuthMethod>\n");
    if (pReqUserAuthMethod) {
        printf("\tTradingDay [%s]\n", pReqUserAuthMethod->TradingDay);
        printf("\tBrokerID [%s]\n", pReqUserAuthMethod->BrokerID);
        printf("\tUserID [%s]\n", pReqUserAuthMethod->UserID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqUserAuthMethod>\n");

    return m_pApi->ReqUserAuthMethod(pReqUserAuthMethod, nRequestID);
};

int CTraderApi::ReqGenUserCaptcha(CThostFtdcReqGenUserCaptchaField *pReqGenUserCaptcha, int nRequestID) {
    printf("<ReqGenUserCaptcha>\n");
    if (pReqGenUserCaptcha) {
        printf("\tTradingDay [%s]\n", pReqGenUserCaptcha->TradingDay);
        printf("\tBrokerID [%s]\n", pReqGenUserCaptcha->BrokerID);
        printf("\tUserID [%s]\n", pReqGenUserCaptcha->UserID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqGenUserCaptcha>\n");

    return m_pApi->ReqGenUserCaptcha(pReqGenUserCaptcha, nRequestID);
};

int CTraderApi::ReqGenUserText(CThostFtdcReqGenUserTextField *pReqGenUserText, int nRequestID) {
    printf("<ReqGenUserText>\n");
    if (pReqGenUserText) {
        printf("\tTradingDay [%s]\n", pReqGenUserText->TradingDay);
        printf("\tBrokerID [%s]\n", pReqGenUserText->BrokerID);
        printf("\tUserID [%s]\n", pReqGenUserText->UserID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqGenUserText>\n");

    return m_pApi->ReqGenUserText(pReqGenUserText, nRequestID);
};

int CTraderApi::ReqUserLoginWithCaptcha(CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha, int nRequestID) {
    printf("<ReqUserLoginWithCaptcha>\n");
    if (pReqUserLoginWithCaptcha) {
        printf("\tTradingDay [%s]\n", pReqUserLoginWithCaptcha->TradingDay);
        printf("\tBrokerID [%s]\n", pReqUserLoginWithCaptcha->BrokerID);
        printf("\tUserID [%s]\n", pReqUserLoginWithCaptcha->UserID);
        printf("\tPassword [%s]\n", pReqUserLoginWithCaptcha->Password);
        printf("\tUserProductInfo [%s]\n", pReqUserLoginWithCaptcha->UserProductInfo);
        printf("\tInterfaceProductInfo [%s]\n", pReqUserLoginWithCaptcha->InterfaceProductInfo);
        printf("\tProtocolInfo [%s]\n", pReqUserLoginWithCaptcha->ProtocolInfo);
        printf("\tMacAddress [%s]\n", pReqUserLoginWithCaptcha->MacAddress);
        printf("\treserve1 [%s]\n", pReqUserLoginWithCaptcha->reserve1);
        printf("\tLoginRemark [%s]\n", pReqUserLoginWithCaptcha->LoginRemark);
        printf("\tCaptcha [%s]\n", pReqUserLoginWithCaptcha->Captcha);
        printf("\tClientIPAddress [%s]\n", pReqUserLoginWithCaptcha->ClientIPAddress);
        printf("\tClientIPPort [%d]\n", pReqUserLoginWithCaptcha->ClientIPPort);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqUserLoginWithCaptcha>\n");

    return m_pApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, nRequestID);
};

int CTraderApi::ReqUserLoginWithText(CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText, int nRequestID) {
    printf("<ReqUserLoginWithText>\n");
    if (pReqUserLoginWithText) {
        printf("\tTradingDay [%s]\n", pReqUserLoginWithText->TradingDay);
        printf("\tBrokerID [%s]\n", pReqUserLoginWithText->BrokerID);
        printf("\tUserID [%s]\n", pReqUserLoginWithText->UserID);
        printf("\tPassword [%s]\n", pReqUserLoginWithText->Password);
        printf("\tUserProductInfo [%s]\n", pReqUserLoginWithText->UserProductInfo);
        printf("\tInterfaceProductInfo [%s]\n", pReqUserLoginWithText->InterfaceProductInfo);
        printf("\tProtocolInfo [%s]\n", pReqUserLoginWithText->ProtocolInfo);
        printf("\tMacAddress [%s]\n", pReqUserLoginWithText->MacAddress);
        printf("\treserve1 [%s]\n", pReqUserLoginWithText->reserve1);
        printf("\tLoginRemark [%s]\n", pReqUserLoginWithText->LoginRemark);
        printf("\tText [%s]\n", pReqUserLoginWithText->Text);
        printf("\tClientIPAddress [%s]\n", pReqUserLoginWithText->ClientIPAddress);
        printf("\tClientIPPort [%d]\n", pReqUserLoginWithText->ClientIPPort);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqUserLoginWithText>\n");

    return m_pApi->ReqUserLoginWithText(pReqUserLoginWithText, nRequestID);
};

int CTraderApi::ReqUserLoginWithOTP(CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP, int nRequestID) {
    printf("<ReqUserLoginWithOTP>\n");
    if (pReqUserLoginWithOTP) {
        printf("\tTradingDay [%s]\n", pReqUserLoginWithOTP->TradingDay);
        printf("\tBrokerID [%s]\n", pReqUserLoginWithOTP->BrokerID);
        printf("\tUserID [%s]\n", pReqUserLoginWithOTP->UserID);
        printf("\tPassword [%s]\n", pReqUserLoginWithOTP->Password);
        printf("\tUserProductInfo [%s]\n", pReqUserLoginWithOTP->UserProductInfo);
        printf("\tInterfaceProductInfo [%s]\n", pReqUserLoginWithOTP->InterfaceProductInfo);
        printf("\tProtocolInfo [%s]\n", pReqUserLoginWithOTP->ProtocolInfo);
        printf("\tMacAddress [%s]\n", pReqUserLoginWithOTP->MacAddress);
        printf("\treserve1 [%s]\n", pReqUserLoginWithOTP->reserve1);
        printf("\tLoginRemark [%s]\n", pReqUserLoginWithOTP->LoginRemark);
        printf("\tOTPPassword [%s]\n", pReqUserLoginWithOTP->OTPPassword);
        printf("\tClientIPAddress [%s]\n", pReqUserLoginWithOTP->ClientIPAddress);
        printf("\tClientIPPort [%d]\n", pReqUserLoginWithOTP->ClientIPPort);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqUserLoginWithOTP>\n");

    return m_pApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, nRequestID);
};

int CTraderApi::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) {
    printf("<ReqOrderInsert>\n");
    if (pInputOrder) {
        printf("\tBrokerID [%s]\n", pInputOrder->BrokerID);
        printf("\tInvestorID [%s]\n", pInputOrder->InvestorID);
        printf("\treserve1 [%s]\n", pInputOrder->reserve1);
        printf("\tOrderRef [%s]\n", pInputOrder->OrderRef);
        printf("\tUserID [%s]\n", pInputOrder->UserID);
        printf("\tCombOffsetFlag [%s]\n", pInputOrder->CombOffsetFlag);
        printf("\tCombHedgeFlag [%s]\n", pInputOrder->CombHedgeFlag);
        printf("\tGTDDate [%s]\n", pInputOrder->GTDDate);
        printf("\tBusinessUnit [%s]\n", pInputOrder->BusinessUnit);
        printf("\tExchangeID [%s]\n", pInputOrder->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pInputOrder->InvestUnitID);
        printf("\tAccountID [%s]\n", pInputOrder->AccountID);
        printf("\tCurrencyID [%s]\n", pInputOrder->CurrencyID);
        printf("\tClientID [%s]\n", pInputOrder->ClientID);
        printf("\treserve2 [%s]\n", pInputOrder->reserve2);
        printf("\tMacAddress [%s]\n", pInputOrder->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputOrder->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputOrder->IPAddress);
        printf("\tVolumeTotalOriginal [%d]\n", pInputOrder->VolumeTotalOriginal);
        printf("\tMinVolume [%d]\n", pInputOrder->MinVolume);
        printf("\tIsAutoSuspend [%d]\n", pInputOrder->IsAutoSuspend);
        printf("\tRequestID [%d]\n", pInputOrder->RequestID);
        printf("\tUserForceClose [%d]\n", pInputOrder->UserForceClose);
        printf("\tIsSwapOrder [%d]\n", pInputOrder->IsSwapOrder);
        printf("\tOrderPriceType [%c]\n", pInputOrder->OrderPriceType);
        printf("\tDirection [%c]\n", pInputOrder->Direction);
        printf("\tTimeCondition [%c]\n", pInputOrder->TimeCondition);
        printf("\tVolumeCondition [%c]\n", pInputOrder->VolumeCondition);
        printf("\tContingentCondition [%c]\n", pInputOrder->ContingentCondition);
        printf("\tForceCloseReason [%c]\n", pInputOrder->ForceCloseReason);
        printf("\tLimitPrice [%.8lf]\n", pInputOrder->LimitPrice);
        printf("\tStopPrice [%.8lf]\n", pInputOrder->StopPrice);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqOrderInsert>\n");

    return m_pApi->ReqOrderInsert(pInputOrder, nRequestID);
};

int CTraderApi::ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID) {
    printf("<ReqParkedOrderInsert>\n");
    if (pParkedOrder) {
        printf("\tBrokerID [%s]\n", pParkedOrder->BrokerID);
        printf("\tInvestorID [%s]\n", pParkedOrder->InvestorID);
        printf("\treserve1 [%s]\n", pParkedOrder->reserve1);
        printf("\tOrderRef [%s]\n", pParkedOrder->OrderRef);
        printf("\tUserID [%s]\n", pParkedOrder->UserID);
        printf("\tCombOffsetFlag [%s]\n", pParkedOrder->CombOffsetFlag);
        printf("\tCombHedgeFlag [%s]\n", pParkedOrder->CombHedgeFlag);
        printf("\tGTDDate [%s]\n", pParkedOrder->GTDDate);
        printf("\tBusinessUnit [%s]\n", pParkedOrder->BusinessUnit);
        printf("\tExchangeID [%s]\n", pParkedOrder->ExchangeID);
        printf("\tParkedOrderID [%s]\n", pParkedOrder->ParkedOrderID);
        printf("\tErrorMsg [%s]\n", pParkedOrder->ErrorMsg);
        printf("\tAccountID [%s]\n", pParkedOrder->AccountID);
        printf("\tCurrencyID [%s]\n", pParkedOrder->CurrencyID);
        printf("\tClientID [%s]\n", pParkedOrder->ClientID);
        printf("\tInvestUnitID [%s]\n", pParkedOrder->InvestUnitID);
        printf("\treserve2 [%s]\n", pParkedOrder->reserve2);
        printf("\tMacAddress [%s]\n", pParkedOrder->MacAddress);
        printf("\tInstrumentID [%s]\n", pParkedOrder->InstrumentID);
        printf("\tIPAddress [%s]\n", pParkedOrder->IPAddress);
        printf("\tVolumeTotalOriginal [%d]\n", pParkedOrder->VolumeTotalOriginal);
        printf("\tMinVolume [%d]\n", pParkedOrder->MinVolume);
        printf("\tIsAutoSuspend [%d]\n", pParkedOrder->IsAutoSuspend);
        printf("\tRequestID [%d]\n", pParkedOrder->RequestID);
        printf("\tUserForceClose [%d]\n", pParkedOrder->UserForceClose);
        printf("\tErrorID [%d]\n", pParkedOrder->ErrorID);
        printf("\tIsSwapOrder [%d]\n", pParkedOrder->IsSwapOrder);
        printf("\tOrderPriceType [%c]\n", pParkedOrder->OrderPriceType);
        printf("\tDirection [%c]\n", pParkedOrder->Direction);
        printf("\tTimeCondition [%c]\n", pParkedOrder->TimeCondition);
        printf("\tVolumeCondition [%c]\n", pParkedOrder->VolumeCondition);
        printf("\tContingentCondition [%c]\n", pParkedOrder->ContingentCondition);
        printf("\tForceCloseReason [%c]\n", pParkedOrder->ForceCloseReason);
        printf("\tUserType [%c]\n", pParkedOrder->UserType);
        printf("\tStatus [%c]\n", pParkedOrder->Status);
        printf("\tLimitPrice [%.8lf]\n", pParkedOrder->LimitPrice);
        printf("\tStopPrice [%.8lf]\n", pParkedOrder->StopPrice);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqParkedOrderInsert>\n");

    return m_pApi->ReqParkedOrderInsert(pParkedOrder, nRequestID);
};

int CTraderApi::ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID) {
    printf("<ReqParkedOrderAction>\n");
    if (pParkedOrderAction) {
        printf("\tBrokerID [%s]\n", pParkedOrderAction->BrokerID);
        printf("\tInvestorID [%s]\n", pParkedOrderAction->InvestorID);
        printf("\tOrderRef [%s]\n", pParkedOrderAction->OrderRef);
        printf("\tExchangeID [%s]\n", pParkedOrderAction->ExchangeID);
        printf("\tOrderSysID [%s]\n", pParkedOrderAction->OrderSysID);
        printf("\tUserID [%s]\n", pParkedOrderAction->UserID);
        printf("\treserve1 [%s]\n", pParkedOrderAction->reserve1);
        printf("\tParkedOrderActionID [%s]\n", pParkedOrderAction->ParkedOrderActionID);
        printf("\tErrorMsg [%s]\n", pParkedOrderAction->ErrorMsg);
        printf("\tInvestUnitID [%s]\n", pParkedOrderAction->InvestUnitID);
        printf("\treserve2 [%s]\n", pParkedOrderAction->reserve2);
        printf("\tMacAddress [%s]\n", pParkedOrderAction->MacAddress);
        printf("\tInstrumentID [%s]\n", pParkedOrderAction->InstrumentID);
        printf("\tIPAddress [%s]\n", pParkedOrderAction->IPAddress);
        printf("\tOrderActionRef [%d]\n", pParkedOrderAction->OrderActionRef);
        printf("\tRequestID [%d]\n", pParkedOrderAction->RequestID);
        printf("\tFrontID [%d]\n", pParkedOrderAction->FrontID);
        printf("\tSessionID [%d]\n", pParkedOrderAction->SessionID);
        printf("\tVolumeChange [%d]\n", pParkedOrderAction->VolumeChange);
        printf("\tErrorID [%d]\n", pParkedOrderAction->ErrorID);
        printf("\tActionFlag [%c]\n", pParkedOrderAction->ActionFlag);
        printf("\tUserType [%c]\n", pParkedOrderAction->UserType);
        printf("\tStatus [%c]\n", pParkedOrderAction->Status);
        printf("\tLimitPrice [%.8lf]\n", pParkedOrderAction->LimitPrice);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqParkedOrderAction>\n");

    return m_pApi->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
};

int CTraderApi::ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) {
    printf("<ReqOrderAction>\n");
    if (pInputOrderAction) {
        printf("\tBrokerID [%s]\n", pInputOrderAction->BrokerID);
        printf("\tInvestorID [%s]\n", pInputOrderAction->InvestorID);
        printf("\tOrderRef [%s]\n", pInputOrderAction->OrderRef);
        printf("\tExchangeID [%s]\n", pInputOrderAction->ExchangeID);
        printf("\tOrderSysID [%s]\n", pInputOrderAction->OrderSysID);
        printf("\tUserID [%s]\n", pInputOrderAction->UserID);
        printf("\treserve1 [%s]\n", pInputOrderAction->reserve1);
        printf("\tInvestUnitID [%s]\n", pInputOrderAction->InvestUnitID);
        printf("\treserve2 [%s]\n", pInputOrderAction->reserve2);
        printf("\tMacAddress [%s]\n", pInputOrderAction->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputOrderAction->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputOrderAction->IPAddress);
        printf("\tOrderActionRef [%d]\n", pInputOrderAction->OrderActionRef);
        printf("\tRequestID [%d]\n", pInputOrderAction->RequestID);
        printf("\tFrontID [%d]\n", pInputOrderAction->FrontID);
        printf("\tSessionID [%d]\n", pInputOrderAction->SessionID);
        printf("\tVolumeChange [%d]\n", pInputOrderAction->VolumeChange);
        printf("\tActionFlag [%c]\n", pInputOrderAction->ActionFlag);
        printf("\tLimitPrice [%.8lf]\n", pInputOrderAction->LimitPrice);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqOrderAction>\n");

    return m_pApi->ReqOrderAction(pInputOrderAction, nRequestID);
};

int CTraderApi::ReqQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, int nRequestID) {
    printf("<ReqQryMaxOrderVolume>\n");
    if (pQryMaxOrderVolume) {
        printf("\tBrokerID [%s]\n", pQryMaxOrderVolume->BrokerID);
        printf("\tInvestorID [%s]\n", pQryMaxOrderVolume->InvestorID);
        printf("\treserve1 [%s]\n", pQryMaxOrderVolume->reserve1);
        printf("\tExchangeID [%s]\n", pQryMaxOrderVolume->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryMaxOrderVolume->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryMaxOrderVolume->InstrumentID);
        printf("\tMaxVolume [%d]\n", pQryMaxOrderVolume->MaxVolume);
        printf("\tDirection [%c]\n", pQryMaxOrderVolume->Direction);
        printf("\tOffsetFlag [%c]\n", pQryMaxOrderVolume->OffsetFlag);
        printf("\tHedgeFlag [%c]\n", pQryMaxOrderVolume->HedgeFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryMaxOrderVolume>\n");

    return m_pApi->ReqQryMaxOrderVolume(pQryMaxOrderVolume, nRequestID);
};

int CTraderApi::ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID) {
    printf("<ReqSettlementInfoConfirm>\n");
    if (pSettlementInfoConfirm) {
        printf("\tBrokerID [%s]\n", pSettlementInfoConfirm->BrokerID);
        printf("\tInvestorID [%s]\n", pSettlementInfoConfirm->InvestorID);
        printf("\tConfirmDate [%s]\n", pSettlementInfoConfirm->ConfirmDate);
        printf("\tConfirmTime [%s]\n", pSettlementInfoConfirm->ConfirmTime);
        printf("\tAccountID [%s]\n", pSettlementInfoConfirm->AccountID);
        printf("\tCurrencyID [%s]\n", pSettlementInfoConfirm->CurrencyID);
        printf("\tSettlementID [%d]\n", pSettlementInfoConfirm->SettlementID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqSettlementInfoConfirm>\n");

    return m_pApi->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
};

int CTraderApi::ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID) {
    printf("<ReqRemoveParkedOrder>\n");
    if (pRemoveParkedOrder) {
        printf("\tBrokerID [%s]\n", pRemoveParkedOrder->BrokerID);
        printf("\tInvestorID [%s]\n", pRemoveParkedOrder->InvestorID);
        printf("\tParkedOrderID [%s]\n", pRemoveParkedOrder->ParkedOrderID);
        printf("\tInvestUnitID [%s]\n", pRemoveParkedOrder->InvestUnitID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqRemoveParkedOrder>\n");

    return m_pApi->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
};

int CTraderApi::ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID) {
    printf("<ReqRemoveParkedOrderAction>\n");
    if (pRemoveParkedOrderAction) {
        printf("\tBrokerID [%s]\n", pRemoveParkedOrderAction->BrokerID);
        printf("\tInvestorID [%s]\n", pRemoveParkedOrderAction->InvestorID);
        printf("\tParkedOrderActionID [%s]\n", pRemoveParkedOrderAction->ParkedOrderActionID);
        printf("\tInvestUnitID [%s]\n", pRemoveParkedOrderAction->InvestUnitID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqRemoveParkedOrderAction>\n");

    return m_pApi->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
};

int CTraderApi::ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID) {
    printf("<ReqExecOrderInsert>\n");
    if (pInputExecOrder) {
        printf("\tBrokerID [%s]\n", pInputExecOrder->BrokerID);
        printf("\tInvestorID [%s]\n", pInputExecOrder->InvestorID);
        printf("\treserve1 [%s]\n", pInputExecOrder->reserve1);
        printf("\tExecOrderRef [%s]\n", pInputExecOrder->ExecOrderRef);
        printf("\tUserID [%s]\n", pInputExecOrder->UserID);
        printf("\tBusinessUnit [%s]\n", pInputExecOrder->BusinessUnit);
        printf("\tExchangeID [%s]\n", pInputExecOrder->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pInputExecOrder->InvestUnitID);
        printf("\tAccountID [%s]\n", pInputExecOrder->AccountID);
        printf("\tCurrencyID [%s]\n", pInputExecOrder->CurrencyID);
        printf("\tClientID [%s]\n", pInputExecOrder->ClientID);
        printf("\treserve2 [%s]\n", pInputExecOrder->reserve2);
        printf("\tMacAddress [%s]\n", pInputExecOrder->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputExecOrder->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputExecOrder->IPAddress);
        printf("\tVolume [%d]\n", pInputExecOrder->Volume);
        printf("\tRequestID [%d]\n", pInputExecOrder->RequestID);
        printf("\tOffsetFlag [%c]\n", pInputExecOrder->OffsetFlag);
        printf("\tHedgeFlag [%c]\n", pInputExecOrder->HedgeFlag);
        printf("\tActionType [%c]\n", pInputExecOrder->ActionType);
        printf("\tPosiDirection [%c]\n", pInputExecOrder->PosiDirection);
        printf("\tReservePositionFlag [%c]\n", pInputExecOrder->ReservePositionFlag);
        printf("\tCloseFlag [%c]\n", pInputExecOrder->CloseFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqExecOrderInsert>\n");

    return m_pApi->ReqExecOrderInsert(pInputExecOrder, nRequestID);
};

int CTraderApi::ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID) {
    printf("<ReqExecOrderAction>\n");
    if (pInputExecOrderAction) {
        printf("\tBrokerID [%s]\n", pInputExecOrderAction->BrokerID);
        printf("\tInvestorID [%s]\n", pInputExecOrderAction->InvestorID);
        printf("\tExecOrderRef [%s]\n", pInputExecOrderAction->ExecOrderRef);
        printf("\tExchangeID [%s]\n", pInputExecOrderAction->ExchangeID);
        printf("\tExecOrderSysID [%s]\n", pInputExecOrderAction->ExecOrderSysID);
        printf("\tUserID [%s]\n", pInputExecOrderAction->UserID);
        printf("\treserve1 [%s]\n", pInputExecOrderAction->reserve1);
        printf("\tInvestUnitID [%s]\n", pInputExecOrderAction->InvestUnitID);
        printf("\treserve2 [%s]\n", pInputExecOrderAction->reserve2);
        printf("\tMacAddress [%s]\n", pInputExecOrderAction->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputExecOrderAction->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputExecOrderAction->IPAddress);
        printf("\tExecOrderActionRef [%d]\n", pInputExecOrderAction->ExecOrderActionRef);
        printf("\tRequestID [%d]\n", pInputExecOrderAction->RequestID);
        printf("\tFrontID [%d]\n", pInputExecOrderAction->FrontID);
        printf("\tSessionID [%d]\n", pInputExecOrderAction->SessionID);
        printf("\tActionFlag [%c]\n", pInputExecOrderAction->ActionFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqExecOrderAction>\n");

    return m_pApi->ReqExecOrderAction(pInputExecOrderAction, nRequestID);
};

int CTraderApi::ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID) {
    printf("<ReqForQuoteInsert>\n");
    if (pInputForQuote) {
        printf("\tBrokerID [%s]\n", pInputForQuote->BrokerID);
        printf("\tInvestorID [%s]\n", pInputForQuote->InvestorID);
        printf("\treserve1 [%s]\n", pInputForQuote->reserve1);
        printf("\tForQuoteRef [%s]\n", pInputForQuote->ForQuoteRef);
        printf("\tUserID [%s]\n", pInputForQuote->UserID);
        printf("\tExchangeID [%s]\n", pInputForQuote->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pInputForQuote->InvestUnitID);
        printf("\treserve2 [%s]\n", pInputForQuote->reserve2);
        printf("\tMacAddress [%s]\n", pInputForQuote->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputForQuote->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputForQuote->IPAddress);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqForQuoteInsert>\n");

    return m_pApi->ReqForQuoteInsert(pInputForQuote, nRequestID);
};

int CTraderApi::ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID) {
    printf("<ReqQuoteInsert>\n");
    if (pInputQuote) {
        printf("\tBrokerID [%s]\n", pInputQuote->BrokerID);
        printf("\tInvestorID [%s]\n", pInputQuote->InvestorID);
        printf("\treserve1 [%s]\n", pInputQuote->reserve1);
        printf("\tQuoteRef [%s]\n", pInputQuote->QuoteRef);
        printf("\tUserID [%s]\n", pInputQuote->UserID);
        printf("\tBusinessUnit [%s]\n", pInputQuote->BusinessUnit);
        printf("\tAskOrderRef [%s]\n", pInputQuote->AskOrderRef);
        printf("\tBidOrderRef [%s]\n", pInputQuote->BidOrderRef);
        printf("\tForQuoteSysID [%s]\n", pInputQuote->ForQuoteSysID);
        printf("\tExchangeID [%s]\n", pInputQuote->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pInputQuote->InvestUnitID);
        printf("\tClientID [%s]\n", pInputQuote->ClientID);
        printf("\treserve2 [%s]\n", pInputQuote->reserve2);
        printf("\tMacAddress [%s]\n", pInputQuote->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputQuote->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputQuote->IPAddress);
        printf("\tReplaceSysID [%s]\n", pInputQuote->ReplaceSysID);
        printf("\tAskVolume [%d]\n", pInputQuote->AskVolume);
        printf("\tBidVolume [%d]\n", pInputQuote->BidVolume);
        printf("\tRequestID [%d]\n", pInputQuote->RequestID);
        printf("\tAskOffsetFlag [%c]\n", pInputQuote->AskOffsetFlag);
        printf("\tBidOffsetFlag [%c]\n", pInputQuote->BidOffsetFlag);
        printf("\tAskHedgeFlag [%c]\n", pInputQuote->AskHedgeFlag);
        printf("\tBidHedgeFlag [%c]\n", pInputQuote->BidHedgeFlag);
        printf("\tAskPrice [%.8lf]\n", pInputQuote->AskPrice);
        printf("\tBidPrice [%.8lf]\n", pInputQuote->BidPrice);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQuoteInsert>\n");

    return m_pApi->ReqQuoteInsert(pInputQuote, nRequestID);
};

int CTraderApi::ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID) {
    printf("<ReqQuoteAction>\n");
    if (pInputQuoteAction) {
        printf("\tBrokerID [%s]\n", pInputQuoteAction->BrokerID);
        printf("\tInvestorID [%s]\n", pInputQuoteAction->InvestorID);
        printf("\tQuoteRef [%s]\n", pInputQuoteAction->QuoteRef);
        printf("\tExchangeID [%s]\n", pInputQuoteAction->ExchangeID);
        printf("\tQuoteSysID [%s]\n", pInputQuoteAction->QuoteSysID);
        printf("\tUserID [%s]\n", pInputQuoteAction->UserID);
        printf("\treserve1 [%s]\n", pInputQuoteAction->reserve1);
        printf("\tInvestUnitID [%s]\n", pInputQuoteAction->InvestUnitID);
        printf("\tClientID [%s]\n", pInputQuoteAction->ClientID);
        printf("\treserve2 [%s]\n", pInputQuoteAction->reserve2);
        printf("\tMacAddress [%s]\n", pInputQuoteAction->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputQuoteAction->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputQuoteAction->IPAddress);
        printf("\tQuoteActionRef [%d]\n", pInputQuoteAction->QuoteActionRef);
        printf("\tRequestID [%d]\n", pInputQuoteAction->RequestID);
        printf("\tFrontID [%d]\n", pInputQuoteAction->FrontID);
        printf("\tSessionID [%d]\n", pInputQuoteAction->SessionID);
        printf("\tActionFlag [%c]\n", pInputQuoteAction->ActionFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQuoteAction>\n");

    return m_pApi->ReqQuoteAction(pInputQuoteAction, nRequestID);
};

int CTraderApi::ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, int nRequestID) {
    printf("<ReqBatchOrderAction>\n");
    if (pInputBatchOrderAction) {
        printf("\tBrokerID [%s]\n", pInputBatchOrderAction->BrokerID);
        printf("\tInvestorID [%s]\n", pInputBatchOrderAction->InvestorID);
        printf("\tExchangeID [%s]\n", pInputBatchOrderAction->ExchangeID);
        printf("\tUserID [%s]\n", pInputBatchOrderAction->UserID);
        printf("\tInvestUnitID [%s]\n", pInputBatchOrderAction->InvestUnitID);
        printf("\treserve1 [%s]\n", pInputBatchOrderAction->reserve1);
        printf("\tMacAddress [%s]\n", pInputBatchOrderAction->MacAddress);
        printf("\tIPAddress [%s]\n", pInputBatchOrderAction->IPAddress);
        printf("\tOrderActionRef [%d]\n", pInputBatchOrderAction->OrderActionRef);
        printf("\tRequestID [%d]\n", pInputBatchOrderAction->RequestID);
        printf("\tFrontID [%d]\n", pInputBatchOrderAction->FrontID);
        printf("\tSessionID [%d]\n", pInputBatchOrderAction->SessionID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqBatchOrderAction>\n");

    return m_pApi->ReqBatchOrderAction(pInputBatchOrderAction, nRequestID);
};

int CTraderApi::ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, int nRequestID) {
    printf("<ReqOptionSelfCloseInsert>\n");
    if (pInputOptionSelfClose) {
        printf("\tBrokerID [%s]\n", pInputOptionSelfClose->BrokerID);
        printf("\tInvestorID [%s]\n", pInputOptionSelfClose->InvestorID);
        printf("\treserve1 [%s]\n", pInputOptionSelfClose->reserve1);
        printf("\tOptionSelfCloseRef [%s]\n", pInputOptionSelfClose->OptionSelfCloseRef);
        printf("\tUserID [%s]\n", pInputOptionSelfClose->UserID);
        printf("\tBusinessUnit [%s]\n", pInputOptionSelfClose->BusinessUnit);
        printf("\tExchangeID [%s]\n", pInputOptionSelfClose->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pInputOptionSelfClose->InvestUnitID);
        printf("\tAccountID [%s]\n", pInputOptionSelfClose->AccountID);
        printf("\tCurrencyID [%s]\n", pInputOptionSelfClose->CurrencyID);
        printf("\tClientID [%s]\n", pInputOptionSelfClose->ClientID);
        printf("\treserve2 [%s]\n", pInputOptionSelfClose->reserve2);
        printf("\tMacAddress [%s]\n", pInputOptionSelfClose->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputOptionSelfClose->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputOptionSelfClose->IPAddress);
        printf("\tVolume [%d]\n", pInputOptionSelfClose->Volume);
        printf("\tRequestID [%d]\n", pInputOptionSelfClose->RequestID);
        printf("\tHedgeFlag [%c]\n", pInputOptionSelfClose->HedgeFlag);
        printf("\tOptSelfCloseFlag [%c]\n", pInputOptionSelfClose->OptSelfCloseFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqOptionSelfCloseInsert>\n");

    return m_pApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, nRequestID);
};

int CTraderApi::ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, int nRequestID) {
    printf("<ReqOptionSelfCloseAction>\n");
    if (pInputOptionSelfCloseAction) {
        printf("\tBrokerID [%s]\n", pInputOptionSelfCloseAction->BrokerID);
        printf("\tInvestorID [%s]\n", pInputOptionSelfCloseAction->InvestorID);
        printf("\tOptionSelfCloseRef [%s]\n", pInputOptionSelfCloseAction->OptionSelfCloseRef);
        printf("\tExchangeID [%s]\n", pInputOptionSelfCloseAction->ExchangeID);
        printf("\tOptionSelfCloseSysID [%s]\n", pInputOptionSelfCloseAction->OptionSelfCloseSysID);
        printf("\tUserID [%s]\n", pInputOptionSelfCloseAction->UserID);
        printf("\treserve1 [%s]\n", pInputOptionSelfCloseAction->reserve1);
        printf("\tInvestUnitID [%s]\n", pInputOptionSelfCloseAction->InvestUnitID);
        printf("\treserve2 [%s]\n", pInputOptionSelfCloseAction->reserve2);
        printf("\tMacAddress [%s]\n", pInputOptionSelfCloseAction->MacAddress);
        printf("\tInstrumentID [%s]\n", pInputOptionSelfCloseAction->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputOptionSelfCloseAction->IPAddress);
        printf("\tOptionSelfCloseActionRef [%d]\n", pInputOptionSelfCloseAction->OptionSelfCloseActionRef);
        printf("\tRequestID [%d]\n", pInputOptionSelfCloseAction->RequestID);
        printf("\tFrontID [%d]\n", pInputOptionSelfCloseAction->FrontID);
        printf("\tSessionID [%d]\n", pInputOptionSelfCloseAction->SessionID);
        printf("\tActionFlag [%c]\n", pInputOptionSelfCloseAction->ActionFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqOptionSelfCloseAction>\n");

    return m_pApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, nRequestID);
};

int CTraderApi::ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID) {
    printf("<ReqCombActionInsert>\n");
    if (pInputCombAction) {
        printf("\tBrokerID [%s]\n", pInputCombAction->BrokerID);
        printf("\tInvestorID [%s]\n", pInputCombAction->InvestorID);
        printf("\treserve1 [%s]\n", pInputCombAction->reserve1);
        printf("\tCombActionRef [%s]\n", pInputCombAction->CombActionRef);
        printf("\tUserID [%s]\n", pInputCombAction->UserID);
        printf("\tExchangeID [%s]\n", pInputCombAction->ExchangeID);
        printf("\treserve2 [%s]\n", pInputCombAction->reserve2);
        printf("\tMacAddress [%s]\n", pInputCombAction->MacAddress);
        printf("\tInvestUnitID [%s]\n", pInputCombAction->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pInputCombAction->InstrumentID);
        printf("\tIPAddress [%s]\n", pInputCombAction->IPAddress);
        printf("\tVolume [%d]\n", pInputCombAction->Volume);
        printf("\tFrontID [%d]\n", pInputCombAction->FrontID);
        printf("\tSessionID [%d]\n", pInputCombAction->SessionID);
        printf("\tDirection [%c]\n", pInputCombAction->Direction);
        printf("\tCombDirection [%c]\n", pInputCombAction->CombDirection);
        printf("\tHedgeFlag [%c]\n", pInputCombAction->HedgeFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqCombActionInsert>\n");

    return m_pApi->ReqCombActionInsert(pInputCombAction, nRequestID);
};

int CTraderApi::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) {
    printf("<ReqQryOrder>\n");
    if (pQryOrder) {
        printf("\tBrokerID [%s]\n", pQryOrder->BrokerID);
        printf("\tInvestorID [%s]\n", pQryOrder->InvestorID);
        printf("\treserve1 [%s]\n", pQryOrder->reserve1);
        printf("\tExchangeID [%s]\n", pQryOrder->ExchangeID);
        printf("\tOrderSysID [%s]\n", pQryOrder->OrderSysID);
        printf("\tInsertTimeStart [%s]\n", pQryOrder->InsertTimeStart);
        printf("\tInsertTimeEnd [%s]\n", pQryOrder->InsertTimeEnd);
        printf("\tInvestUnitID [%s]\n", pQryOrder->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryOrder->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryOrder>\n");

    return m_pApi->ReqQryOrder(pQryOrder, nRequestID);
};

int CTraderApi::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) {
    printf("<ReqQryTrade>\n");
    if (pQryTrade) {
        printf("\tBrokerID [%s]\n", pQryTrade->BrokerID);
        printf("\tInvestorID [%s]\n", pQryTrade->InvestorID);
        printf("\treserve1 [%s]\n", pQryTrade->reserve1);
        printf("\tExchangeID [%s]\n", pQryTrade->ExchangeID);
        printf("\tTradeID [%s]\n", pQryTrade->TradeID);
        printf("\tTradeTimeStart [%s]\n", pQryTrade->TradeTimeStart);
        printf("\tTradeTimeEnd [%s]\n", pQryTrade->TradeTimeEnd);
        printf("\tInvestUnitID [%s]\n", pQryTrade->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryTrade->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryTrade>\n");

    return m_pApi->ReqQryTrade(pQryTrade, nRequestID);
};

int CTraderApi::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) {
    printf("<ReqQryInvestorPosition>\n");
    if (pQryInvestorPosition) {
        printf("\tBrokerID [%s]\n", pQryInvestorPosition->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInvestorPosition->InvestorID);
        printf("\treserve1 [%s]\n", pQryInvestorPosition->reserve1);
        printf("\tExchangeID [%s]\n", pQryInvestorPosition->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryInvestorPosition->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryInvestorPosition->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInvestorPosition>\n");

    return m_pApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
};

int CTraderApi::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) {
    printf("<ReqQryTradingAccount>\n");
    if (pQryTradingAccount) {
        printf("\tBrokerID [%s]\n", pQryTradingAccount->BrokerID);
        printf("\tInvestorID [%s]\n", pQryTradingAccount->InvestorID);
        printf("\tCurrencyID [%s]\n", pQryTradingAccount->CurrencyID);
        printf("\tAccountID [%s]\n", pQryTradingAccount->AccountID);
        printf("\tBizType [%c]\n", pQryTradingAccount->BizType);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryTradingAccount>\n");

    return m_pApi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
};

int CTraderApi::ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID) {
    printf("<ReqQryInvestor>\n");
    if (pQryInvestor) {
        printf("\tBrokerID [%s]\n", pQryInvestor->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInvestor->InvestorID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInvestor>\n");

    return m_pApi->ReqQryInvestor(pQryInvestor, nRequestID);
};

int CTraderApi::ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID) {
    printf("<ReqQryTradingCode>\n");
    if (pQryTradingCode) {
        printf("\tBrokerID [%s]\n", pQryTradingCode->BrokerID);
        printf("\tInvestorID [%s]\n", pQryTradingCode->InvestorID);
        printf("\tExchangeID [%s]\n", pQryTradingCode->ExchangeID);
        printf("\tClientID [%s]\n", pQryTradingCode->ClientID);
        printf("\tInvestUnitID [%s]\n", pQryTradingCode->InvestUnitID);
        printf("\tClientIDType [%c]\n", pQryTradingCode->ClientIDType);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryTradingCode>\n");

    return m_pApi->ReqQryTradingCode(pQryTradingCode, nRequestID);
};

int CTraderApi::ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID) {
    printf("<ReqQryInstrumentMarginRate>\n");
    if (pQryInstrumentMarginRate) {
        printf("\tBrokerID [%s]\n", pQryInstrumentMarginRate->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInstrumentMarginRate->InvestorID);
        printf("\treserve1 [%s]\n", pQryInstrumentMarginRate->reserve1);
        printf("\tExchangeID [%s]\n", pQryInstrumentMarginRate->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryInstrumentMarginRate->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryInstrumentMarginRate->InstrumentID);
        printf("\tHedgeFlag [%c]\n", pQryInstrumentMarginRate->HedgeFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInstrumentMarginRate>\n");

    return m_pApi->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
};

int CTraderApi::ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID) {
    printf("<ReqQryInstrumentCommissionRate>\n");
    if (pQryInstrumentCommissionRate) {
        printf("\tBrokerID [%s]\n", pQryInstrumentCommissionRate->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInstrumentCommissionRate->InvestorID);
        printf("\treserve1 [%s]\n", pQryInstrumentCommissionRate->reserve1);
        printf("\tExchangeID [%s]\n", pQryInstrumentCommissionRate->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryInstrumentCommissionRate->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryInstrumentCommissionRate->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInstrumentCommissionRate>\n");

    return m_pApi->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
};

int CTraderApi::ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID) {
    printf("<ReqQryExchange>\n");
    if (pQryExchange) {
        printf("\tExchangeID [%s]\n", pQryExchange->ExchangeID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryExchange>\n");

    return m_pApi->ReqQryExchange(pQryExchange, nRequestID);
};

int CTraderApi::ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID) {
    printf("<ReqQryProduct>\n");
    if (pQryProduct) {
        printf("\treserve1 [%s]\n", pQryProduct->reserve1);
        printf("\tExchangeID [%s]\n", pQryProduct->ExchangeID);
        printf("\tProductID [%s]\n", pQryProduct->ProductID);
        printf("\tProductClass [%c]\n", pQryProduct->ProductClass);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryProduct>\n");

    return m_pApi->ReqQryProduct(pQryProduct, nRequestID);
};

int CTraderApi::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID) {
    printf("<ReqQryInstrument>\n");
    if (pQryInstrument) {
        printf("\treserve1 [%s]\n", pQryInstrument->reserve1);
        printf("\tExchangeID [%s]\n", pQryInstrument->ExchangeID);
        printf("\treserve2 [%s]\n", pQryInstrument->reserve2);
        printf("\treserve3 [%s]\n", pQryInstrument->reserve3);
        printf("\tInstrumentID [%s]\n", pQryInstrument->InstrumentID);
        printf("\tExchangeInstID [%s]\n", pQryInstrument->ExchangeInstID);
        printf("\tProductID [%s]\n", pQryInstrument->ProductID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInstrument>\n");

    return m_pApi->ReqQryInstrument(pQryInstrument, nRequestID);
};

int CTraderApi::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID) {
    printf("<ReqQryDepthMarketData>\n");
    if (pQryDepthMarketData) {
        printf("\treserve1 [%s]\n", pQryDepthMarketData->reserve1);
        printf("\tExchangeID [%s]\n", pQryDepthMarketData->ExchangeID);
        printf("\tInstrumentID [%s]\n", pQryDepthMarketData->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryDepthMarketData>\n");

    return m_pApi->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
};

int CTraderApi::ReqQryTraderOffer(CThostFtdcQryTraderOfferField *pQryTraderOffer, int nRequestID) {
    printf("<ReqQryTraderOffer>\n");
    if (pQryTraderOffer) {
        printf("\tExchangeID [%s]\n", pQryTraderOffer->ExchangeID);
        printf("\tParticipantID [%s]\n", pQryTraderOffer->ParticipantID);
        printf("\tTraderID [%s]\n", pQryTraderOffer->TraderID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryTraderOffer>\n");

    return m_pApi->ReqQryTraderOffer(pQryTraderOffer, nRequestID);
};

int CTraderApi::ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID) {
    printf("<ReqQrySettlementInfo>\n");
    if (pQrySettlementInfo) {
        printf("\tBrokerID [%s]\n", pQrySettlementInfo->BrokerID);
        printf("\tInvestorID [%s]\n", pQrySettlementInfo->InvestorID);
        printf("\tTradingDay [%s]\n", pQrySettlementInfo->TradingDay);
        printf("\tAccountID [%s]\n", pQrySettlementInfo->AccountID);
        printf("\tCurrencyID [%s]\n", pQrySettlementInfo->CurrencyID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQrySettlementInfo>\n");

    return m_pApi->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
};

int CTraderApi::ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID) {
    printf("<ReqQryTransferBank>\n");
    if (pQryTransferBank) {
        printf("\tBankID [%s]\n", pQryTransferBank->BankID);
        printf("\tBankBrchID [%s]\n", pQryTransferBank->BankBrchID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryTransferBank>\n");

    return m_pApi->ReqQryTransferBank(pQryTransferBank, nRequestID);
};

int CTraderApi::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID) {
    printf("<ReqQryInvestorPositionDetail>\n");
    if (pQryInvestorPositionDetail) {
        printf("\tBrokerID [%s]\n", pQryInvestorPositionDetail->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInvestorPositionDetail->InvestorID);
        printf("\treserve1 [%s]\n", pQryInvestorPositionDetail->reserve1);
        printf("\tExchangeID [%s]\n", pQryInvestorPositionDetail->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryInvestorPositionDetail->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryInvestorPositionDetail->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInvestorPositionDetail>\n");

    return m_pApi->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
};

int CTraderApi::ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID) {
    printf("<ReqQryNotice>\n");
    if (pQryNotice) {
        printf("\tBrokerID [%s]\n", pQryNotice->BrokerID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryNotice>\n");

    return m_pApi->ReqQryNotice(pQryNotice, nRequestID);
};

int CTraderApi::ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID) {
    printf("<ReqQrySettlementInfoConfirm>\n");
    if (pQrySettlementInfoConfirm) {
        printf("\tBrokerID [%s]\n", pQrySettlementInfoConfirm->BrokerID);
        printf("\tInvestorID [%s]\n", pQrySettlementInfoConfirm->InvestorID);
        printf("\tAccountID [%s]\n", pQrySettlementInfoConfirm->AccountID);
        printf("\tCurrencyID [%s]\n", pQrySettlementInfoConfirm->CurrencyID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQrySettlementInfoConfirm>\n");

    return m_pApi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
};

int CTraderApi::ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail,
                                                    int nRequestID) {
    printf("<ReqQryInvestorPositionCombineDetail>\n");
    if (pQryInvestorPositionCombineDetail) {
        printf("\tBrokerID [%s]\n", pQryInvestorPositionCombineDetail->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInvestorPositionCombineDetail->InvestorID);
        printf("\treserve1 [%s]\n", pQryInvestorPositionCombineDetail->reserve1);
        printf("\tExchangeID [%s]\n", pQryInvestorPositionCombineDetail->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryInvestorPositionCombineDetail->InvestUnitID);
        printf("\tCombInstrumentID [%s]\n", pQryInvestorPositionCombineDetail->CombInstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInvestorPositionCombineDetail>\n");

    return m_pApi->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
};

int CTraderApi::ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID) {
    printf("<ReqQryCFMMCTradingAccountKey>\n");
    if (pQryCFMMCTradingAccountKey) {
        printf("\tBrokerID [%s]\n", pQryCFMMCTradingAccountKey->BrokerID);
        printf("\tInvestorID [%s]\n", pQryCFMMCTradingAccountKey->InvestorID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryCFMMCTradingAccountKey>\n");

    return m_pApi->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, nRequestID);
};

int CTraderApi::ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID) {
    printf("<ReqQryEWarrantOffset>\n");
    if (pQryEWarrantOffset) {
        printf("\tBrokerID [%s]\n", pQryEWarrantOffset->BrokerID);
        printf("\tInvestorID [%s]\n", pQryEWarrantOffset->InvestorID);
        printf("\tExchangeID [%s]\n", pQryEWarrantOffset->ExchangeID);
        printf("\treserve1 [%s]\n", pQryEWarrantOffset->reserve1);
        printf("\tInvestUnitID [%s]\n", pQryEWarrantOffset->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryEWarrantOffset->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryEWarrantOffset>\n");

    return m_pApi->ReqQryEWarrantOffset(pQryEWarrantOffset, nRequestID);
};

int CTraderApi::ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin,
                                                 int nRequestID) {
    printf("<ReqQryInvestorProductGroupMargin>\n");
    if (pQryInvestorProductGroupMargin) {
        printf("\tBrokerID [%s]\n", pQryInvestorProductGroupMargin->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInvestorProductGroupMargin->InvestorID);
        printf("\treserve1 [%s]\n", pQryInvestorProductGroupMargin->reserve1);
        printf("\tExchangeID [%s]\n", pQryInvestorProductGroupMargin->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryInvestorProductGroupMargin->InvestUnitID);
        printf("\tProductGroupID [%s]\n", pQryInvestorProductGroupMargin->ProductGroupID);
        printf("\tHedgeFlag [%c]\n", pQryInvestorProductGroupMargin->HedgeFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInvestorProductGroupMargin>\n");

    return m_pApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, nRequestID);
};

int CTraderApi::ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID) {
    printf("<ReqQryExchangeMarginRate>\n");
    if (pQryExchangeMarginRate) {
        printf("\tBrokerID [%s]\n", pQryExchangeMarginRate->BrokerID);
        printf("\treserve1 [%s]\n", pQryExchangeMarginRate->reserve1);
        printf("\tExchangeID [%s]\n", pQryExchangeMarginRate->ExchangeID);
        printf("\tInstrumentID [%s]\n", pQryExchangeMarginRate->InstrumentID);
        printf("\tHedgeFlag [%c]\n", pQryExchangeMarginRate->HedgeFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryExchangeMarginRate>\n");

    return m_pApi->ReqQryExchangeMarginRate(pQryExchangeMarginRate, nRequestID);
};

int CTraderApi::ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID) {
    printf("<ReqQryExchangeMarginRateAdjust>\n");
    if (pQryExchangeMarginRateAdjust) {
        printf("\tBrokerID [%s]\n", pQryExchangeMarginRateAdjust->BrokerID);
        printf("\treserve1 [%s]\n", pQryExchangeMarginRateAdjust->reserve1);
        printf("\tInstrumentID [%s]\n", pQryExchangeMarginRateAdjust->InstrumentID);
        printf("\tHedgeFlag [%c]\n", pQryExchangeMarginRateAdjust->HedgeFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryExchangeMarginRateAdjust>\n");

    return m_pApi->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, nRequestID);
};

int CTraderApi::ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID) {
    printf("<ReqQryExchangeRate>\n");
    if (pQryExchangeRate) {
        printf("\tBrokerID [%s]\n", pQryExchangeRate->BrokerID);
        printf("\tFromCurrencyID [%s]\n", pQryExchangeRate->FromCurrencyID);
        printf("\tToCurrencyID [%s]\n", pQryExchangeRate->ToCurrencyID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryExchangeRate>\n");

    return m_pApi->ReqQryExchangeRate(pQryExchangeRate, nRequestID);
};

int CTraderApi::ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID) {
    printf("<ReqQrySecAgentACIDMap>\n");
    if (pQrySecAgentACIDMap) {
        printf("\tBrokerID [%s]\n", pQrySecAgentACIDMap->BrokerID);
        printf("\tUserID [%s]\n", pQrySecAgentACIDMap->UserID);
        printf("\tAccountID [%s]\n", pQrySecAgentACIDMap->AccountID);
        printf("\tCurrencyID [%s]\n", pQrySecAgentACIDMap->CurrencyID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQrySecAgentACIDMap>\n");

    return m_pApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, nRequestID);
};

int CTraderApi::ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate, int nRequestID) {
    printf("<ReqQryProductExchRate>\n");
    if (pQryProductExchRate) {
        printf("\treserve1 [%s]\n", pQryProductExchRate->reserve1);
        printf("\tExchangeID [%s]\n", pQryProductExchRate->ExchangeID);
        printf("\tProductID [%s]\n", pQryProductExchRate->ProductID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryProductExchRate>\n");

    return m_pApi->ReqQryProductExchRate(pQryProductExchRate, nRequestID);
};

int CTraderApi::ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID) {
    printf("<ReqQryProductGroup>\n");
    if (pQryProductGroup) {
        printf("\treserve1 [%s]\n", pQryProductGroup->reserve1);
        printf("\tExchangeID [%s]\n", pQryProductGroup->ExchangeID);
        printf("\tProductID [%s]\n", pQryProductGroup->ProductID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryProductGroup>\n");

    return m_pApi->ReqQryProductGroup(pQryProductGroup, nRequestID);
};

int CTraderApi::ReqQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField *pQryMMInstrumentCommissionRate,
                                                 int nRequestID) {
    printf("<ReqQryMMInstrumentCommissionRate>\n");
    if (pQryMMInstrumentCommissionRate) {
        printf("\tBrokerID [%s]\n", pQryMMInstrumentCommissionRate->BrokerID);
        printf("\tInvestorID [%s]\n", pQryMMInstrumentCommissionRate->InvestorID);
        printf("\treserve1 [%s]\n", pQryMMInstrumentCommissionRate->reserve1);
        printf("\tInstrumentID [%s]\n", pQryMMInstrumentCommissionRate->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryMMInstrumentCommissionRate>\n");

    return m_pApi->ReqQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate, nRequestID);
};

int CTraderApi::ReqQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField *pQryMMOptionInstrCommRate, int nRequestID) {
    printf("<ReqQryMMOptionInstrCommRate>\n");
    if (pQryMMOptionInstrCommRate) {
        printf("\tBrokerID [%s]\n", pQryMMOptionInstrCommRate->BrokerID);
        printf("\tInvestorID [%s]\n", pQryMMOptionInstrCommRate->InvestorID);
        printf("\treserve1 [%s]\n", pQryMMOptionInstrCommRate->reserve1);
        printf("\tInstrumentID [%s]\n", pQryMMOptionInstrCommRate->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryMMOptionInstrCommRate>\n");

    return m_pApi->ReqQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate, nRequestID);
};

int CTraderApi::ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField *pQryInstrumentOrderCommRate, int nRequestID) {
    printf("<ReqQryInstrumentOrderCommRate>\n");
    if (pQryInstrumentOrderCommRate) {
        printf("\tBrokerID [%s]\n", pQryInstrumentOrderCommRate->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInstrumentOrderCommRate->InvestorID);
        printf("\treserve1 [%s]\n", pQryInstrumentOrderCommRate->reserve1);
        printf("\tInstrumentID [%s]\n", pQryInstrumentOrderCommRate->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInstrumentOrderCommRate>\n");

    return m_pApi->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, nRequestID);
};

int CTraderApi::ReqQrySecAgentTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) {
    printf("<ReqQrySecAgentTradingAccount>\n");
    if (pQryTradingAccount) {
        printf("\tBrokerID [%s]\n", pQryTradingAccount->BrokerID);
        printf("\tInvestorID [%s]\n", pQryTradingAccount->InvestorID);
        printf("\tCurrencyID [%s]\n", pQryTradingAccount->CurrencyID);
        printf("\tAccountID [%s]\n", pQryTradingAccount->AccountID);
        printf("\tBizType [%c]\n", pQryTradingAccount->BizType);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQrySecAgentTradingAccount>\n");

    return m_pApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, nRequestID);
};

int CTraderApi::ReqQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode, int nRequestID) {
    printf("<ReqQrySecAgentCheckMode>\n");
    if (pQrySecAgentCheckMode) {
        printf("\tBrokerID [%s]\n", pQrySecAgentCheckMode->BrokerID);
        printf("\tInvestorID [%s]\n", pQrySecAgentCheckMode->InvestorID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQrySecAgentCheckMode>\n");

    return m_pApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, nRequestID);
};

int CTraderApi::ReqQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField *pQrySecAgentTradeInfo, int nRequestID) {
    printf("<ReqQrySecAgentTradeInfo>\n");
    if (pQrySecAgentTradeInfo) {
        printf("\tBrokerID [%s]\n", pQrySecAgentTradeInfo->BrokerID);
        printf("\tBrokerSecAgentID [%s]\n", pQrySecAgentTradeInfo->BrokerSecAgentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQrySecAgentTradeInfo>\n");

    return m_pApi->ReqQrySecAgentTradeInfo(pQrySecAgentTradeInfo, nRequestID);
};

int CTraderApi::ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID) {
    printf("<ReqQryOptionInstrTradeCost>\n");
    if (pQryOptionInstrTradeCost) {
        printf("\tBrokerID [%s]\n", pQryOptionInstrTradeCost->BrokerID);
        printf("\tInvestorID [%s]\n", pQryOptionInstrTradeCost->InvestorID);
        printf("\treserve1 [%s]\n", pQryOptionInstrTradeCost->reserve1);
        printf("\tExchangeID [%s]\n", pQryOptionInstrTradeCost->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryOptionInstrTradeCost->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryOptionInstrTradeCost->InstrumentID);
        printf("\tHedgeFlag [%c]\n", pQryOptionInstrTradeCost->HedgeFlag);
        printf("\tInputPrice [%.8lf]\n", pQryOptionInstrTradeCost->InputPrice);
        printf("\tUnderlyingPrice [%.8lf]\n", pQryOptionInstrTradeCost->UnderlyingPrice);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryOptionInstrTradeCost>\n");

    return m_pApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, nRequestID);
};

int CTraderApi::ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID) {
    printf("<ReqQryOptionInstrCommRate>\n");
    if (pQryOptionInstrCommRate) {
        printf("\tBrokerID [%s]\n", pQryOptionInstrCommRate->BrokerID);
        printf("\tInvestorID [%s]\n", pQryOptionInstrCommRate->InvestorID);
        printf("\treserve1 [%s]\n", pQryOptionInstrCommRate->reserve1);
        printf("\tExchangeID [%s]\n", pQryOptionInstrCommRate->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryOptionInstrCommRate->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryOptionInstrCommRate->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryOptionInstrCommRate>\n");

    return m_pApi->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, nRequestID);
};

int CTraderApi::ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder, int nRequestID) {
    printf("<ReqQryExecOrder>\n");
    if (pQryExecOrder) {
        printf("\tBrokerID [%s]\n", pQryExecOrder->BrokerID);
        printf("\tInvestorID [%s]\n", pQryExecOrder->InvestorID);
        printf("\treserve1 [%s]\n", pQryExecOrder->reserve1);
        printf("\tExchangeID [%s]\n", pQryExecOrder->ExchangeID);
        printf("\tExecOrderSysID [%s]\n", pQryExecOrder->ExecOrderSysID);
        printf("\tInsertTimeStart [%s]\n", pQryExecOrder->InsertTimeStart);
        printf("\tInsertTimeEnd [%s]\n", pQryExecOrder->InsertTimeEnd);
        printf("\tInstrumentID [%s]\n", pQryExecOrder->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryExecOrder>\n");

    return m_pApi->ReqQryExecOrder(pQryExecOrder, nRequestID);
};

int CTraderApi::ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID) {
    printf("<ReqQryForQuote>\n");
    if (pQryForQuote) {
        printf("\tBrokerID [%s]\n", pQryForQuote->BrokerID);
        printf("\tInvestorID [%s]\n", pQryForQuote->InvestorID);
        printf("\treserve1 [%s]\n", pQryForQuote->reserve1);
        printf("\tExchangeID [%s]\n", pQryForQuote->ExchangeID);
        printf("\tInsertTimeStart [%s]\n", pQryForQuote->InsertTimeStart);
        printf("\tInsertTimeEnd [%s]\n", pQryForQuote->InsertTimeEnd);
        printf("\tInvestUnitID [%s]\n", pQryForQuote->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryForQuote->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryForQuote>\n");

    return m_pApi->ReqQryForQuote(pQryForQuote, nRequestID);
};

int CTraderApi::ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID) {
    printf("<ReqQryQuote>\n");
    if (pQryQuote) {
        printf("\tBrokerID [%s]\n", pQryQuote->BrokerID);
        printf("\tInvestorID [%s]\n", pQryQuote->InvestorID);
        printf("\treserve1 [%s]\n", pQryQuote->reserve1);
        printf("\tExchangeID [%s]\n", pQryQuote->ExchangeID);
        printf("\tQuoteSysID [%s]\n", pQryQuote->QuoteSysID);
        printf("\tInsertTimeStart [%s]\n", pQryQuote->InsertTimeStart);
        printf("\tInsertTimeEnd [%s]\n", pQryQuote->InsertTimeEnd);
        printf("\tInvestUnitID [%s]\n", pQryQuote->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryQuote->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryQuote>\n");

    return m_pApi->ReqQryQuote(pQryQuote, nRequestID);
};

int CTraderApi::ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose, int nRequestID) {
    printf("<ReqQryOptionSelfClose>\n");
    if (pQryOptionSelfClose) {
        printf("\tBrokerID [%s]\n", pQryOptionSelfClose->BrokerID);
        printf("\tInvestorID [%s]\n", pQryOptionSelfClose->InvestorID);
        printf("\treserve1 [%s]\n", pQryOptionSelfClose->reserve1);
        printf("\tExchangeID [%s]\n", pQryOptionSelfClose->ExchangeID);
        printf("\tOptionSelfCloseSysID [%s]\n", pQryOptionSelfClose->OptionSelfCloseSysID);
        printf("\tInsertTimeStart [%s]\n", pQryOptionSelfClose->InsertTimeStart);
        printf("\tInsertTimeEnd [%s]\n", pQryOptionSelfClose->InsertTimeEnd);
        printf("\tInstrumentID [%s]\n", pQryOptionSelfClose->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryOptionSelfClose>\n");

    return m_pApi->ReqQryOptionSelfClose(pQryOptionSelfClose, nRequestID);
};

int CTraderApi::ReqQryInvestUnit(CThostFtdcQryInvestUnitField *pQryInvestUnit, int nRequestID) {
    printf("<ReqQryInvestUnit>\n");
    if (pQryInvestUnit) {
        printf("\tBrokerID [%s]\n", pQryInvestUnit->BrokerID);
        printf("\tInvestorID [%s]\n", pQryInvestUnit->InvestorID);
        printf("\tInvestUnitID [%s]\n", pQryInvestUnit->InvestUnitID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryInvestUnit>\n");

    return m_pApi->ReqQryInvestUnit(pQryInvestUnit, nRequestID);
};

int CTraderApi::ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID) {
    printf("<ReqQryCombInstrumentGuard>\n");
    if (pQryCombInstrumentGuard) {
        printf("\tBrokerID [%s]\n", pQryCombInstrumentGuard->BrokerID);
        printf("\treserve1 [%s]\n", pQryCombInstrumentGuard->reserve1);
        printf("\tExchangeID [%s]\n", pQryCombInstrumentGuard->ExchangeID);
        printf("\tInstrumentID [%s]\n", pQryCombInstrumentGuard->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryCombInstrumentGuard>\n");

    return m_pApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, nRequestID);
};

int CTraderApi::ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction, int nRequestID) {
    printf("<ReqQryCombAction>\n");
    if (pQryCombAction) {
        printf("\tBrokerID [%s]\n", pQryCombAction->BrokerID);
        printf("\tInvestorID [%s]\n", pQryCombAction->InvestorID);
        printf("\treserve1 [%s]\n", pQryCombAction->reserve1);
        printf("\tExchangeID [%s]\n", pQryCombAction->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryCombAction->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryCombAction->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryCombAction>\n");

    return m_pApi->ReqQryCombAction(pQryCombAction, nRequestID);
};

int CTraderApi::ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID) {
    printf("<ReqQryTransferSerial>\n");
    if (pQryTransferSerial) {
        printf("\tBrokerID [%s]\n", pQryTransferSerial->BrokerID);
        printf("\tAccountID [%s]\n", pQryTransferSerial->AccountID);
        printf("\tBankID [%s]\n", pQryTransferSerial->BankID);
        printf("\tCurrencyID [%s]\n", pQryTransferSerial->CurrencyID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryTransferSerial>\n");

    return m_pApi->ReqQryTransferSerial(pQryTransferSerial, nRequestID);
};

int CTraderApi::ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID) {
    printf("<ReqQryAccountregister>\n");
    if (pQryAccountregister) {
        printf("\tBrokerID [%s]\n", pQryAccountregister->BrokerID);
        printf("\tAccountID [%s]\n", pQryAccountregister->AccountID);
        printf("\tBankID [%s]\n", pQryAccountregister->BankID);
        printf("\tBankBranchID [%s]\n", pQryAccountregister->BankBranchID);
        printf("\tCurrencyID [%s]\n", pQryAccountregister->CurrencyID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryAccountregister>\n");

    return m_pApi->ReqQryAccountregister(pQryAccountregister, nRequestID);
};

int CTraderApi::ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID) {
    printf("<ReqQryContractBank>\n");
    if (pQryContractBank) {
        printf("\tBrokerID [%s]\n", pQryContractBank->BrokerID);
        printf("\tBankID [%s]\n", pQryContractBank->BankID);
        printf("\tBankBrchID [%s]\n", pQryContractBank->BankBrchID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryContractBank>\n");

    return m_pApi->ReqQryContractBank(pQryContractBank, nRequestID);
};

int CTraderApi::ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID) {
    printf("<ReqQryParkedOrder>\n");
    if (pQryParkedOrder) {
        printf("\tBrokerID [%s]\n", pQryParkedOrder->BrokerID);
        printf("\tInvestorID [%s]\n", pQryParkedOrder->InvestorID);
        printf("\treserve1 [%s]\n", pQryParkedOrder->reserve1);
        printf("\tExchangeID [%s]\n", pQryParkedOrder->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryParkedOrder->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryParkedOrder->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryParkedOrder>\n");

    return m_pApi->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
};

int CTraderApi::ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID) {
    printf("<ReqQryParkedOrderAction>\n");
    if (pQryParkedOrderAction) {
        printf("\tBrokerID [%s]\n", pQryParkedOrderAction->BrokerID);
        printf("\tInvestorID [%s]\n", pQryParkedOrderAction->InvestorID);
        printf("\treserve1 [%s]\n", pQryParkedOrderAction->reserve1);
        printf("\tExchangeID [%s]\n", pQryParkedOrderAction->ExchangeID);
        printf("\tInvestUnitID [%s]\n", pQryParkedOrderAction->InvestUnitID);
        printf("\tInstrumentID [%s]\n", pQryParkedOrderAction->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryParkedOrderAction>\n");

    return m_pApi->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
};

int CTraderApi::ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID) {
    printf("<ReqQryTradingNotice>\n");
    if (pQryTradingNotice) {
        printf("\tBrokerID [%s]\n", pQryTradingNotice->BrokerID);
        printf("\tInvestorID [%s]\n", pQryTradingNotice->InvestorID);
        printf("\tInvestUnitID [%s]\n", pQryTradingNotice->InvestUnitID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryTradingNotice>\n");

    return m_pApi->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
};

int CTraderApi::ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID) {
    printf("<ReqQryBrokerTradingParams>\n");
    if (pQryBrokerTradingParams) {
        printf("\tBrokerID [%s]\n", pQryBrokerTradingParams->BrokerID);
        printf("\tInvestorID [%s]\n", pQryBrokerTradingParams->InvestorID);
        printf("\tCurrencyID [%s]\n", pQryBrokerTradingParams->CurrencyID);
        printf("\tAccountID [%s]\n", pQryBrokerTradingParams->AccountID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryBrokerTradingParams>\n");

    return m_pApi->ReqQryBrokerTradingParams(pQryBrokerTradingParams, nRequestID);
};

int CTraderApi::ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID) {
    printf("<ReqQryBrokerTradingAlgos>\n");
    if (pQryBrokerTradingAlgos) {
        printf("\tBrokerID [%s]\n", pQryBrokerTradingAlgos->BrokerID);
        printf("\tExchangeID [%s]\n", pQryBrokerTradingAlgos->ExchangeID);
        printf("\treserve1 [%s]\n", pQryBrokerTradingAlgos->reserve1);
        printf("\tInstrumentID [%s]\n", pQryBrokerTradingAlgos->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryBrokerTradingAlgos>\n");

    return m_pApi->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, nRequestID);
};

int CTraderApi::ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken,
                                                 int nRequestID) {
    printf("<ReqQueryCFMMCTradingAccountToken>\n");
    if (pQueryCFMMCTradingAccountToken) {
        printf("\tBrokerID [%s]\n", pQueryCFMMCTradingAccountToken->BrokerID);
        printf("\tInvestorID [%s]\n", pQueryCFMMCTradingAccountToken->InvestorID);
        printf("\tInvestUnitID [%s]\n", pQueryCFMMCTradingAccountToken->InvestUnitID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQueryCFMMCTradingAccountToken>\n");

    return m_pApi->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, nRequestID);
};

int CTraderApi::ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID) {
    printf("<ReqFromBankToFutureByFuture>\n");
    if (pReqTransfer) {
        printf("\tTradeCode [%s]\n", pReqTransfer->TradeCode);
        printf("\tBankID [%s]\n", pReqTransfer->BankID);
        printf("\tBankBranchID [%s]\n", pReqTransfer->BankBranchID);
        printf("\tBrokerID [%s]\n", pReqTransfer->BrokerID);
        printf("\tBrokerBranchID [%s]\n", pReqTransfer->BrokerBranchID);
        printf("\tTradeDate [%s]\n", pReqTransfer->TradeDate);
        printf("\tTradeTime [%s]\n", pReqTransfer->TradeTime);
        printf("\tBankSerial [%s]\n", pReqTransfer->BankSerial);
        printf("\tTradingDay [%s]\n", pReqTransfer->TradingDay);
        printf("\tCustomerName [%s]\n", pReqTransfer->CustomerName);
        printf("\tIdentifiedCardNo [%s]\n", pReqTransfer->IdentifiedCardNo);
        printf("\tBankAccount [%s]\n", pReqTransfer->BankAccount);
        printf("\tBankPassWord [%s]\n", pReqTransfer->BankPassWord);
        printf("\tAccountID [%s]\n", pReqTransfer->AccountID);
        printf("\tPassword [%s]\n", pReqTransfer->Password);
        printf("\tUserID [%s]\n", pReqTransfer->UserID);
        printf("\tCurrencyID [%s]\n", pReqTransfer->CurrencyID);
        printf("\tMessage [%s]\n", pReqTransfer->Message);
        printf("\tDigest [%s]\n", pReqTransfer->Digest);
        printf("\tDeviceID [%s]\n", pReqTransfer->DeviceID);
        printf("\tBrokerIDByBank [%s]\n", pReqTransfer->BrokerIDByBank);
        printf("\tBankSecuAcc [%s]\n", pReqTransfer->BankSecuAcc);
        printf("\tOperNo [%s]\n", pReqTransfer->OperNo);
        printf("\tLongCustomerName [%s]\n", pReqTransfer->LongCustomerName);
        printf("\tPlateSerial [%d]\n", pReqTransfer->PlateSerial);
        printf("\tSessionID [%d]\n", pReqTransfer->SessionID);
        printf("\tInstallID [%d]\n", pReqTransfer->InstallID);
        printf("\tFutureSerial [%d]\n", pReqTransfer->FutureSerial);
        printf("\tRequestID [%d]\n", pReqTransfer->RequestID);
        printf("\tTID [%d]\n", pReqTransfer->TID);
        printf("\tLastFragment [%c]\n", pReqTransfer->LastFragment);
        printf("\tIdCardType [%c]\n", pReqTransfer->IdCardType);
        printf("\tCustType [%c]\n", pReqTransfer->CustType);
        printf("\tVerifyCertNoFlag [%c]\n", pReqTransfer->VerifyCertNoFlag);
        printf("\tFeePayFlag [%c]\n", pReqTransfer->FeePayFlag);
        printf("\tBankAccType [%c]\n", pReqTransfer->BankAccType);
        printf("\tBankSecuAccType [%c]\n", pReqTransfer->BankSecuAccType);
        printf("\tBankPwdFlag [%c]\n", pReqTransfer->BankPwdFlag);
        printf("\tSecuPwdFlag [%c]\n", pReqTransfer->SecuPwdFlag);
        printf("\tTransferStatus [%c]\n", pReqTransfer->TransferStatus);
        printf("\tTradeAmount [%.8lf]\n", pReqTransfer->TradeAmount);
        printf("\tFutureFetchAmount [%.8lf]\n", pReqTransfer->FutureFetchAmount);
        printf("\tCustFee [%.8lf]\n", pReqTransfer->CustFee);
        printf("\tBrokerFee [%.8lf]\n", pReqTransfer->BrokerFee);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqFromBankToFutureByFuture>\n");

    return m_pApi->ReqFromBankToFutureByFuture(pReqTransfer, nRequestID);
};

int CTraderApi::ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID) {
    printf("<ReqFromFutureToBankByFuture>\n");
    if (pReqTransfer) {
        printf("\tTradeCode [%s]\n", pReqTransfer->TradeCode);
        printf("\tBankID [%s]\n", pReqTransfer->BankID);
        printf("\tBankBranchID [%s]\n", pReqTransfer->BankBranchID);
        printf("\tBrokerID [%s]\n", pReqTransfer->BrokerID);
        printf("\tBrokerBranchID [%s]\n", pReqTransfer->BrokerBranchID);
        printf("\tTradeDate [%s]\n", pReqTransfer->TradeDate);
        printf("\tTradeTime [%s]\n", pReqTransfer->TradeTime);
        printf("\tBankSerial [%s]\n", pReqTransfer->BankSerial);
        printf("\tTradingDay [%s]\n", pReqTransfer->TradingDay);
        printf("\tCustomerName [%s]\n", pReqTransfer->CustomerName);
        printf("\tIdentifiedCardNo [%s]\n", pReqTransfer->IdentifiedCardNo);
        printf("\tBankAccount [%s]\n", pReqTransfer->BankAccount);
        printf("\tBankPassWord [%s]\n", pReqTransfer->BankPassWord);
        printf("\tAccountID [%s]\n", pReqTransfer->AccountID);
        printf("\tPassword [%s]\n", pReqTransfer->Password);
        printf("\tUserID [%s]\n", pReqTransfer->UserID);
        printf("\tCurrencyID [%s]\n", pReqTransfer->CurrencyID);
        printf("\tMessage [%s]\n", pReqTransfer->Message);
        printf("\tDigest [%s]\n", pReqTransfer->Digest);
        printf("\tDeviceID [%s]\n", pReqTransfer->DeviceID);
        printf("\tBrokerIDByBank [%s]\n", pReqTransfer->BrokerIDByBank);
        printf("\tBankSecuAcc [%s]\n", pReqTransfer->BankSecuAcc);
        printf("\tOperNo [%s]\n", pReqTransfer->OperNo);
        printf("\tLongCustomerName [%s]\n", pReqTransfer->LongCustomerName);
        printf("\tPlateSerial [%d]\n", pReqTransfer->PlateSerial);
        printf("\tSessionID [%d]\n", pReqTransfer->SessionID);
        printf("\tInstallID [%d]\n", pReqTransfer->InstallID);
        printf("\tFutureSerial [%d]\n", pReqTransfer->FutureSerial);
        printf("\tRequestID [%d]\n", pReqTransfer->RequestID);
        printf("\tTID [%d]\n", pReqTransfer->TID);
        printf("\tLastFragment [%c]\n", pReqTransfer->LastFragment);
        printf("\tIdCardType [%c]\n", pReqTransfer->IdCardType);
        printf("\tCustType [%c]\n", pReqTransfer->CustType);
        printf("\tVerifyCertNoFlag [%c]\n", pReqTransfer->VerifyCertNoFlag);
        printf("\tFeePayFlag [%c]\n", pReqTransfer->FeePayFlag);
        printf("\tBankAccType [%c]\n", pReqTransfer->BankAccType);
        printf("\tBankSecuAccType [%c]\n", pReqTransfer->BankSecuAccType);
        printf("\tBankPwdFlag [%c]\n", pReqTransfer->BankPwdFlag);
        printf("\tSecuPwdFlag [%c]\n", pReqTransfer->SecuPwdFlag);
        printf("\tTransferStatus [%c]\n", pReqTransfer->TransferStatus);
        printf("\tTradeAmount [%.8lf]\n", pReqTransfer->TradeAmount);
        printf("\tFutureFetchAmount [%.8lf]\n", pReqTransfer->FutureFetchAmount);
        printf("\tCustFee [%.8lf]\n", pReqTransfer->CustFee);
        printf("\tBrokerFee [%.8lf]\n", pReqTransfer->BrokerFee);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqFromFutureToBankByFuture>\n");

    return m_pApi->ReqFromFutureToBankByFuture(pReqTransfer, nRequestID);
};

int CTraderApi::ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, int nRequestID) {
    printf("<ReqQueryBankAccountMoneyByFuture>\n");
    if (pReqQueryAccount) {
        printf("\tTradeCode [%s]\n", pReqQueryAccount->TradeCode);
        printf("\tBankID [%s]\n", pReqQueryAccount->BankID);
        printf("\tBankBranchID [%s]\n", pReqQueryAccount->BankBranchID);
        printf("\tBrokerID [%s]\n", pReqQueryAccount->BrokerID);
        printf("\tBrokerBranchID [%s]\n", pReqQueryAccount->BrokerBranchID);
        printf("\tTradeDate [%s]\n", pReqQueryAccount->TradeDate);
        printf("\tTradeTime [%s]\n", pReqQueryAccount->TradeTime);
        printf("\tBankSerial [%s]\n", pReqQueryAccount->BankSerial);
        printf("\tTradingDay [%s]\n", pReqQueryAccount->TradingDay);
        printf("\tCustomerName [%s]\n", pReqQueryAccount->CustomerName);
        printf("\tIdentifiedCardNo [%s]\n", pReqQueryAccount->IdentifiedCardNo);
        printf("\tBankAccount [%s]\n", pReqQueryAccount->BankAccount);
        printf("\tBankPassWord [%s]\n", pReqQueryAccount->BankPassWord);
        printf("\tAccountID [%s]\n", pReqQueryAccount->AccountID);
        printf("\tPassword [%s]\n", pReqQueryAccount->Password);
        printf("\tUserID [%s]\n", pReqQueryAccount->UserID);
        printf("\tCurrencyID [%s]\n", pReqQueryAccount->CurrencyID);
        printf("\tDigest [%s]\n", pReqQueryAccount->Digest);
        printf("\tDeviceID [%s]\n", pReqQueryAccount->DeviceID);
        printf("\tBrokerIDByBank [%s]\n", pReqQueryAccount->BrokerIDByBank);
        printf("\tBankSecuAcc [%s]\n", pReqQueryAccount->BankSecuAcc);
        printf("\tOperNo [%s]\n", pReqQueryAccount->OperNo);
        printf("\tLongCustomerName [%s]\n", pReqQueryAccount->LongCustomerName);
        printf("\tPlateSerial [%d]\n", pReqQueryAccount->PlateSerial);
        printf("\tSessionID [%d]\n", pReqQueryAccount->SessionID);
        printf("\tFutureSerial [%d]\n", pReqQueryAccount->FutureSerial);
        printf("\tInstallID [%d]\n", pReqQueryAccount->InstallID);
        printf("\tRequestID [%d]\n", pReqQueryAccount->RequestID);
        printf("\tTID [%d]\n", pReqQueryAccount->TID);
        printf("\tLastFragment [%c]\n", pReqQueryAccount->LastFragment);
        printf("\tIdCardType [%c]\n", pReqQueryAccount->IdCardType);
        printf("\tCustType [%c]\n", pReqQueryAccount->CustType);
        printf("\tVerifyCertNoFlag [%c]\n", pReqQueryAccount->VerifyCertNoFlag);
        printf("\tBankAccType [%c]\n", pReqQueryAccount->BankAccType);
        printf("\tBankSecuAccType [%c]\n", pReqQueryAccount->BankSecuAccType);
        printf("\tBankPwdFlag [%c]\n", pReqQueryAccount->BankPwdFlag);
        printf("\tSecuPwdFlag [%c]\n", pReqQueryAccount->SecuPwdFlag);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQueryBankAccountMoneyByFuture>\n");

    return m_pApi->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, nRequestID);
};

int CTraderApi::ReqQryClassifiedInstrument(CThostFtdcQryClassifiedInstrumentField *pQryClassifiedInstrument, int nRequestID) {
    printf("<ReqQryClassifiedInstrument>\n");
    if (pQryClassifiedInstrument) {
        printf("\tInstrumentID [%s]\n", pQryClassifiedInstrument->InstrumentID);
        printf("\tExchangeID [%s]\n", pQryClassifiedInstrument->ExchangeID);
        printf("\tExchangeInstID [%s]\n", pQryClassifiedInstrument->ExchangeInstID);
        printf("\tProductID [%s]\n", pQryClassifiedInstrument->ProductID);
        printf("\tTradingType [%c]\n", pQryClassifiedInstrument->TradingType);
        printf("\tClassType [%c]\n", pQryClassifiedInstrument->ClassType);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryClassifiedInstrument>\n");

    return m_pApi->ReqQryClassifiedInstrument(pQryClassifiedInstrument, nRequestID);
};

int CTraderApi::ReqQryCombPromotionParam(CThostFtdcQryCombPromotionParamField *pQryCombPromotionParam, int nRequestID) {
    printf("<ReqQryCombPromotionParam>\n");
    if (pQryCombPromotionParam) {
        printf("\tExchangeID [%s]\n", pQryCombPromotionParam->ExchangeID);
        printf("\tInstrumentID [%s]\n", pQryCombPromotionParam->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryCombPromotionParam>\n");

    return m_pApi->ReqQryCombPromotionParam(pQryCombPromotionParam, nRequestID);
};

int CTraderApi::ReqQryRiskSettleInvstPosition(CThostFtdcQryRiskSettleInvstPositionField *pQryRiskSettleInvstPosition, int nRequestID) {
    printf("<ReqQryRiskSettleInvstPosition>\n");
    if (pQryRiskSettleInvstPosition) {
        printf("\tBrokerID [%s]\n", pQryRiskSettleInvstPosition->BrokerID);
        printf("\tInvestorID [%s]\n", pQryRiskSettleInvstPosition->InvestorID);
        printf("\tInstrumentID [%s]\n", pQryRiskSettleInvstPosition->InstrumentID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryRiskSettleInvstPosition>\n");

    return m_pApi->ReqQryRiskSettleInvstPosition(pQryRiskSettleInvstPosition, nRequestID);
};

int CTraderApi::ReqQryRiskSettleProductStatus(CThostFtdcQryRiskSettleProductStatusField *pQryRiskSettleProductStatus, int nRequestID) {
    printf("<ReqQryRiskSettleProductStatus>\n");
    if (pQryRiskSettleProductStatus) {
        printf("\tProductID [%s]\n", pQryRiskSettleProductStatus->ProductID);
    }
    printf("\tnRequestID [%d]\n", nRequestID);
    printf("</ReqQryRiskSettleProductStatus>\n");

    return m_pApi->ReqQryRiskSettleProductStatus(pQryRiskSettleProductStatus, nRequestID);
};
}  // namespace uBEE