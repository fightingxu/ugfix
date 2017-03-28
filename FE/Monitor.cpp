// Monitor.cpp: implementation of the CMonitor class.
//
//////////////////////////////////////////////////////////////////////
// 修改流水：2008-6-11 向FG推送监控信息时，增加操作间的休眠时间
//     更新版本号：ver 1.0.0.1 20080611
//////////////////////////////////////////////////////////////////////
// 修改流水：2008-6-13 ES消息协议变更，状态监控消息组包发生改变
//     更新版本号：ver 1.0.0.2 20080613
//////////////////////////////////////////////////////////////////////
// 修改流水：2008-7-14 ES状态推送协议报文修正，保留前三项：localId, partnerId, status
//     更新版本号：ver 1.0.0.5 20080714
//////////////////////////////////////////////////////////////////////
// 修改流水：2008-12-3 增加异常处理，如果Session状态不正常，则取状态信息时，可能发生异常
//     更新版本号：ver 1.0.0.8 20081203
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Monitor.h"
#include "SessionContainer.h"
#include "FIXData.h"

#include <exception>

#include "com/sungard/cs/fix/fixgateway/api/capi/CFixStatus.h"
#include "com/mintech/utils/fmi/builtin/arrays/FObjectArray.h"
#include "java/lang/Object.h"

using com::sungard::cs::fix::fixgateway::api::capi::CFixStatus;
using com::mintech::utils::fmi::builtin::arrays::FObjectArray;
using java::lang::Object;

#include <algorithm>

#ifdef _SIMU_TEST
Clogfile tlog;
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonitor::CMonitor()
{

}

CMonitor::~CMonitor()
{

}

CShrMonitor CMonitor::create_instance() 
{
	return CShrMonitor(new CMonitor);
}
	
CManagedAPI CMonitor::getManagedAPI() 
{
	return m_managedApi;
}

void CMonitor::setManagedAPI(CManagedAPI CApi) 
{
	m_managedApi = CApi;
}
	
CShrDataQueue CMonitor::getDataQueue() 
{
	return m_dataq;
}

void CMonitor::setDataQueue(CShrDataQueue Dataq) 
{
	m_dataq = Dataq;
}

void CMonitor::run()
{
	std::vector<std::string> m_ses;
	if (g_sesContainer.GetValidSessions(m_ses))
		NormalMonitor(m_ses);
	if (g_sesContainer.GetDelSessions(m_ses))
		SpecialMonitor(m_ses);
}

void CMonitor::NormalMonitor(std::vector<std::string> const& validSes)
{
	ST_SESINFO sesInfo;
	CFixStatus fixStat;
	char m_data[1024*4];
	for (std::vector<std::string>::const_iterator _pCur=validSes.begin(); _pCur!=validSes.end(); ++_pCur) {
		try {
			fixStat = m_managedApi.getStatus(*_pCur);
		}
		catch (JNIException je) {
			std::string strinfo = std::string(je.getMessage())+std::string(je.getStack());
			throw std::bad_exception(strinfo.c_str());
		}
		memset(m_data, 0, sizeof(m_data));
		g_sesContainer.GetValidSesInfo(*_pCur, sesInfo);
		
		int datalen = 0;
		try {
			if (fixStat.getSenderCompID().empty())
				throw std::exception("CFixStatus Object's SenderCompID is NULL!");
			if (fixStat.getTargetCompID().empty())
				throw std::exception("CFixStatus Object's TargetCompID is NULL!");
			datalen = sprintf(m_data,
				"ES%s%c%s%c%d%c%d%c%d%c%s%c%d%c%d%c%d%c%s%c%s%c%s%c%s%c%s",
				fixStat.getSenderCompID().c_str(),
				C_SOH,fixStat.getTargetCompID().c_str(),
				C_SOH,transState(fixStat.getFixState()),
				C_SOH,0,
				C_SOH,transState(fixStat.getPrevFixState()),
				C_SOH,sesInfo.szVer,
				C_SOH,fixStat.getExpectedInSeqNum(),
				C_SOH,fixStat.getExpectedOutSeqNum(),
				C_SOH,fixStat.getStateReasonCode(),
/**				C_SOH,fixStat.getStateReasonText().c_str(),
				C_SOH,fixStat.getCommString().c_str(),
				C_SOH,fixStat.getSupportedReceiveStr().c_str(),
				C_SOH,fixStat.getSupportedSendStr().c_str() */
				C_SOH,"",
				C_SOH,"",
				C_SOH,"",
				C_SOH,"",
				C_SOH,""
			);
		} 
		catch (std::exception &e) {
			OutErrorFile("FE_throwInfo", (char*)e.what(), __FILE__, __LINE__);
			continue;
		}
		catch (...) {
			OutErrorFile("FE_throwInfo", "CFixStatus Object is invalid!", __FILE__, __LINE__);
			continue;
		}
		m_dataq->WriteLine(fixStat.getSenderCompID().c_str(), fixStat.getTargetCompID().c_str(), m_data, datalen);
		mysleep(1);
	}
}

void CMonitor::SpecialMonitor(std::vector<std::string> const& delSes)
{
	ST_SESINFO sesInfo;
	CFixStatus fixStat;
	char m_data[1024*4];
	for (std::vector<std::string>::const_iterator _pCur=delSes.begin(); _pCur!=delSes.end(); ++_pCur) {
		try {
			fixStat = m_managedApi.getStatus(*_pCur);
		}
		catch (JNIException je) {
			std::string strinfo = std::string(je.getMessage())+std::string(je.getStack());
			throw std::bad_exception(strinfo.c_str());
		}
		if (fixStat.getFixState() == 0) {
			memset(m_data, 0, sizeof(m_data));
			g_sesContainer.GetValidSesInfo(*_pCur, sesInfo);
			int datalen = 0;
			try {
				if (fixStat.getSenderCompID().empty())
					throw std::exception("CFixStatus Object's SenderCompID is NULL!");
				if (fixStat.getTargetCompID().empty())
					throw std::exception("CFixStatus Object's TargetCompID is NULL!");
				datalen = sprintf(m_data,
					"ES%s%c%s%c%d%c%d%c%d%c%s%c%d%c%d%c%d%c%s%c%s%c%s%c%s%c%s",
					fixStat.getSenderCompID().c_str(),
					C_SOH,fixStat.getTargetCompID().c_str(),
					C_SOH,0,
					C_SOH,0,
					C_SOH,transState(fixStat.getPrevFixState()),
					C_SOH,sesInfo.szVer,
					C_SOH,fixStat.getExpectedInSeqNum(),
					C_SOH,fixStat.getExpectedOutSeqNum(),
					C_SOH,fixStat.getStateReasonCode(),
					//C_SOH,fixStat.getStateReasonText().c_str(),
					C_SOH,"",
					C_SOH,"",
					C_SOH,"",
					C_SOH,"",
					C_SOH,""
				);
			}
			catch (std::exception &e) {
				OutErrorFile("FE_throwInfo", (char*)e.what(), __FILE__, __LINE__);
			}
			catch (...) {
				OutErrorFile("FE_throwInfo", "CFixStatus Object(Del Session) is invalid!", __FILE__, __LINE__);
			}
			m_dataq->WriteLine(fixStat.getSenderCompID().c_str(), fixStat.getTargetCompID().c_str(), m_data, datalen);
			g_sesContainer.NeedSendDelConferm(*_pCur);
		}
	}
}

/**
 * 1 = Close
 * C = Connecting
 * 2 = Open
 * E = Error
 */
int CMonitor::transState(int oldState)
{
	int retval = -1;
	switch (oldState) {
	case 0:
		retval = 1;
		break;
	case 1:
		retval = 'C';
		break;
	case 2:
		retval = 2;
		break;
	case 3:
	case 4:
		retval = 'E';
		break;
	}
	return retval;
}

int CMonitor::checkState()
{
	return 0;
}
