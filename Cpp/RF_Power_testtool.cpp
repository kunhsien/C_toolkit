long CBBTestItem::RF_power_testtool()
{
	long lErrorCode = SUCCESS;
	CString sTmp = "";
	long lResult = SUCCESS, lResult1 = SUCCESS, lResult2 = SUCCESS, lResult3 = SUCCESS, lResult4 = SUCCESS, lResult5 = SUCCESS;
	long lTempError = SUCCESS;
	int iRetry = DEFAULT_FTM_CMD_RETRY;
	int iTimeout = DEFAULT_FTM_CMD_TIMEOUT;
	int iDelay = DEFAULT_FTM_CMD_DELAY;
	CString csCmd = "", csReturn,csErrMsg,csStatus,sNode,sReturn,csOutcome;
	CString cstrFreqSKU1 = "", cstrFreqSKU2 = "", cstrFreqSKU3 = "", cstrPower = "", cstrFreq = "";
	CArray<CString, CString> casTokenFreq,casAddress;;
	CString csFreqIndex = "", csPowerIndex = "", csDataRateIndex = "",csAddress = "",csRftype = "",sEEPROM_Address = "";
	int iPower = 0, iExpectPower = 0;
	float fFreq = 0.0, fInput = 0.0, fMaxPower = 0.0, fMinPower = 0.0;
	CString csGpibCommand = "", csQuery_Result = "";
	float fFSKTrigger = 0.0, fPowerAttenuation= 0.0;
	float fPathloss = 0.0;
	int initialpowerindex = 0;
	
	USES_CONVERSION;
	
	lErrorCode = SUCCESS;
	AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_ERROR_CODE, 
												FormatStr("Roger321, ErrorCode= %s", g_theApp.GetErrorString(lErrorCode)));

	ViSession viTestSet = g_theApp.m_stTestSet.viSession;
	if (lErrorCode == SUCCESS)
	{
		HRESULT hr = 0;
		COM_CALL(hr = g_theApp.m_IIRfInstAlgPtr->put_ViTestSet(viTestSet))
	}
	
	lErrorCode = SUCCESS;
	AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_ERROR_CODE, 
												FormatStr("Roger213, ErrorCode= %s", g_theApp.GetErrorString(lErrorCode)));

	//////////////////////////////////////////////////////////////////////
	//Set Step information
	g_theApp.Set_Step_Info("read parameter");
	//////////////////////////////////////////////////////////////////////
	int iEnableYDivision = 0; //set default value(0 = auto) for MKD project
	iEnableYDivision = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/EnableYDivision"));
	if(iEnableYDivision <= 0)
		iEnableYDivision = 0;
	int iEnableTrigger = 0; //set default value(0 = Disable, 1 = Enable) for MKD project
	iEnableTrigger = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/EnableTrigger"));
	if(iEnableTrigger <= 0)
		iEnableTrigger = 0;
	int iEnableAttenuation = 0; //set default value(0 = auto) for MKD project
	iEnableAttenuation = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/EnableAttenuation"));
	if(iEnableAttenuation <= 0)
		iEnableAttenuation = 0;

	CString csSymbolRate = g_theApp.m_InParam.GetElemData("/ProgramParams/SymbolRate");
	CString csFSKLength = g_theApp.m_InParam.GetElemData("/ProgramParams/FSKLength");
	float fAttenuation = atof(g_theApp.m_InParam.GetElemData("/ProgramParams/Attenuation"));
	float fFSKTriggerVal = atof(g_theApp.m_InParam.GetElemData("/ProgramParams/FSKTriggerVal"));
	CString csYDivision = g_theApp.m_InParam.GetElemData("/ProgramParams/YDivision");
	int iDelayTime = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/DelayTime"));
	int iExecuteCalibrationTime = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/ExecuteCalibrationTime"));


	lErrorCode = SUCCESS;
	AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_ERROR_CODE, 
												FormatStr("Roger123, ErrorCode= %s", g_theApp.GetErrorString(lErrorCode)));


	//Added by KHLee
	int iExecuteLoopTime = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/ExecuteLoopTime"));
	AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_ERROR_CODE, FormatStr("iExecuteLoopTime Value = %d", iExecuteLoopTime));
	int iRFInputDac = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/RFInputdec"));
	AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_ERROR_CODE, FormatStr("iRFInputDac Value = %d", iRFInputDac));

	HPA
	LPA

	int bLowPower = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/RFInputdec"));


	int bMidPower = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/RFInputdec"));
	
	int bHighPower = atoi(g_theApp.m_InParam.GetElemData("/ProgramParams/RFInputdec"));
	
	//Added by KHLee


	int iFreqSKU = 0;
	int iFreqListSize = 0;
	int iFreqIndex = 0;

	
	if(lErrorCode == SUCCESS)
	{
		if(g_theApp.m_sHWId == "SKU1")
		{
			iFreqSKU = 1;
			iFreqListSize = 2;
			iFreqIndex = 0;
		}
		else if(g_theApp.m_sHWId == "SKU2")
		{
			iFreqSKU = 2;
			iFreqListSize = 2;
			iFreqIndex = 2;
		}
		else if(g_theApp.m_sHWId == "SKU3")
		{
			iFreqSKU = 3;
			iFreqListSize = 1;
			iFreqIndex = 4;
		}
		else if(g_theApp.m_sHWId == "SKU4")
		{
			iFreqSKU = 4;
			iFreqListSize = 2;
			iFreqIndex = 4;
		}
		else if(g_theApp.m_sHWId == "SKU5")
		{
			iFreqSKU = 5;
			iFreqListSize = 2;
			iFreqIndex = 4;
		}
		else if(g_theApp.m_sHWId == "SKU6")
		{
			iFreqSKU = 6;
			iFreqListSize = 2;
			iFreqIndex = 4;
		}
		else if(g_theApp.m_sHWId == "SKU7")
		{
			iFreqSKU = 7;
			iFreqListSize = 1;
			iFreqIndex = 4;
		}
		else if(g_theApp.m_sHWId == "SKU8")
		{
			iFreqSKU = 8;
			iFreqListSize = 2;
			iFreqIndex = 4;
		}
		else
			lErrorCode = INVALID_HW_ID;
	}
	MyXmlParser mxpTest;
	mxpTest.Load(g_theApp.m_sSpecFile);
	S_RKE_SLTx st_RKE_SLTx;
	CString	csRootName = "";
	CArray<CString, CString> casChild;
	int iCount = 0,iDataRateIndex = 0;
	st_RKE_SLTx.pSLItem = new S_RKE_SLTxSKUItem;

	CString csKeyIndex = "";
	
	//DaC_Power Index Range Array
	int casPowerIndex= iRFInputDac;
	

	int iMinIndex = 0 , iMaxIndex = 87;
	float fCurrCarrPower = 0.0, fMaxCarrPower = 0.0, fMinCarrPower = 0.0;
	float fCurrDeviation = 0.0, fMaxDeviation = 0.0, fMinDeviation = 0.0;
	float fCurrFskError = 0.0, fMaxFskError = 0.0, fMinFskError = 0.0;
	float fCurrMagError = 0.0, fMaxMagError = 0.0, fMinMagError = 0.0;
	float fCurrCarrFreqOffset = 0.0, fMaxCarrFreqOffset = 0.0, fMinCarrFreqOffset = 0.0;
	float fTargetpower = 0.0,fThreshold = 0.0;
	
	for(int i=0; i<1 && lErrorCode == SUCCESS; i++)	// 1 key
	{
		// Reset the Instrument
		lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("*RST");
		if(lErrorCode == SUCCESS)
			lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("*CLS");
		// Set FSK Modulation Analysis
		if(lErrorCode == SUCCESS)
			lErrorCode = g_theApp.m_oRfUtility.GPIB_Send(":CONFigure:FSK");
		// Set Filter Setup
		if(lErrorCode == SUCCESS)
			lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("DANalyse:FSK:RADio:STANdard:FILTer:REFerence NONE");

		if(i == 0)
			csKeyIndex = "88";	// Lock key
		else if(i == 1)
			csKeyIndex = "89";	// Unlock key
		else if(i == 2)
			csKeyIndex = "90";	// Trunk key
		else if(i == 3)
			csKeyIndex = "91";	// Panic key

		for(int j=0; j<iFreqListSize && lErrorCode == SUCCESS ; j++)  //2 freq iFreqIndex iFreqIndex+iFreqListSize
		{
			//Get Cable loss
			sNode.Format("/TCPathLossFile/PathLoss/%s/%s/Freq%d/Input", g_theApp.m_sNowTestName, g_theApp.m_sHWId, j);
			lErrorCode = g_theApp.Get_Node_Value_And_Check(g_theApp.m_sPathLossFile, sNode, &sReturn);
			if(lErrorCode == SUCCESS)
				fPathloss = atof(sReturn);
			
			csRootName.Format("/TCSpecFile/TestSpec/%s/%s/Key%d/Freq%d/", g_theApp.m_sNowTestName, g_theApp.m_sHWId, i, j);			
			mxpTest.EnumChild(csRootName, &casChild);
			lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "Enable", &sReturn);
			if(lErrorCode == SUCCESS)
				st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].iEnable = atoi(sReturn);
			
			lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "Frequency", &sReturn);
			if(lErrorCode == SUCCESS)
				st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].csFrequency = sReturn;

			lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "FreqIndex", &sReturn);
			if(lErrorCode == SUCCESS)
				st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].iFreqIndex = atoi(sReturn);

			if(st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].iEnable)
			{
				
				for (int x = 0; x < iExecuteLoopTime; x++)
				{
					for(int k=0; k<3 && lErrorCode == SUCCESS; k++)		// 3 power
					{ 
						mxpTest.SetPosAtChildIndex(csRootName, k+3);
						
						lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "Enable", &sReturn);
						if(lErrorCode == SUCCESS)
							st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].iEnable = atoi(sReturn);
					
						if(st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].iEnable)
						{
							//OutputPower
							if(lErrorCode == SUCCESS)
							{
								lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "OutputPower", &sReturn);
								if(lErrorCode == SUCCESS)
									st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].fOutputPower = atof(sReturn);
							}
							//InitialPowerIndex
							if(lErrorCode == SUCCESS)
							{
								lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "InitialPowerIndex", &sReturn);
								if(lErrorCode == SUCCESS){
									st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].iPowerIndex = atoi(sReturn);
									initialpowerindex = atoi(sReturn);
								}
							}
							//DataRateIndex
							if(lErrorCode == SUCCESS)
							{
								lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "DataRateIndex", &sReturn);
								if(lErrorCode == SUCCESS)
									st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].csDataRateIndex = sReturn;
								
							}

							//Address
							if(lErrorCode == SUCCESS)
							{
							
								lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "Address", &sReturn);
								if(lErrorCode == SUCCESS)
									st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].csAddress = sReturn;
							
								//CArray<CString,CString> casAddress;
								ExtractToken(sReturn, &casAddress, ",");

							}

							// Set Carrier Freq
							if(lErrorCode == SUCCESS)
							{
								csGpibCommand = "DANalyse:CARR:FREQuency " + st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].csFrequency;
								lErrorCode = g_theApp.m_oRfUtility.GPIB_Send(csGpibCommand);
							}
							// Set Auto carrier frequency tracking
							if(lErrorCode == SUCCESS)
								lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("DANalyse:CARR:FREQuency:AUTO ON");

							// Set Symbol Rate
							CArray<CString,CString> casSymbolRate;
							ExtractToken(csSymbolRate, &casSymbolRate, ",");
							if(lErrorCode == SUCCESS)
							{
								iDataRateIndex = atoi(st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].csDataRateIndex);
								csGpibCommand = "DANalyse:FSK:RADio:STANdard:SRATe " + casSymbolRate[(iDataRateIndex-1)];
								lErrorCode = g_theApp.m_oRfUtility.GPIB_Send(csGpibCommand);
							}

							if(lErrorCode == SUCCESS)
							{
								if(iEnableYDivision == 0)	// Set Y Auto Scale
									lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("DANalyse:FSK:VIEW:Y:AUTO");
								else  // Set Scale/DIV value
								{
									csGpibCommand = FormatStr("DANalyse:FSK:VIEW:Y:PDIVision %skHz", csYDivision);
									lErrorCode = g_theApp.m_oRfUtility.GPIB_Send(csGpibCommand);
								}
							}
					
							// Set Meas Length
							if(lErrorCode == SUCCESS)
							{
								csGpibCommand = "DANalyse:FSK:LENGth " + csFSKLength;
								lErrorCode = g_theApp.m_oRfUtility.GPIB_Send(csGpibCommand);
							}
						
							// Set RF Trigger
							if(lErrorCode == SUCCESS && iEnableTrigger == 1)
							{
								lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("DANalyse:FSK:TRIGger:SOURce RFBurst");

								fFSKTrigger = st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].fOutputPower - fFSKTriggerVal;
								csGpibCommand = FormatStr("DANalyse:FSK:TRIGger:LEVel:ABSolute %.2fdBm", fFSKTrigger);
								lErrorCode = g_theApp.m_oRfUtility.GPIB_Send(csGpibCommand);
							}
							// Set Power Attenuation
							if(lErrorCode == SUCCESS)
							{
								if(iEnableAttenuation == 0)	// Set Auto Attenuation
									lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("DANalyse:POWer:ATTenuation:AUTO ON");
								else //Sets the attenuation value
								{
									fPowerAttenuation = st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].fOutputPower + fAttenuation;
									csGpibCommand = FormatStr("DANalyse:POWer:ATTenuation %.2f", fPowerAttenuation);
									lErrorCode = g_theApp.m_oRfUtility.GPIB_Send(csGpibCommand);
								}
							}

							lErrorCode = SUCCESS;
							AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_ERROR_CODE, 
												FormatStr("Roger789, ErrorCode= %s", g_theApp.GetErrorString(lErrorCode)));

							// Set Sweep Single Mode
							if(lErrorCode == SUCCESS)
								lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("DANalyse:CONTinuous 0");

							if(lErrorCode == SUCCESS)
							{
								int iRetest = 0;
								do {
									g_theApp.Set_Step_Info(FormatStr("Retest - %d", iRetest));
									lErrorCode = SUCCESS;
								
									if(lErrorCode == SUCCESS)
									{
										g_theApp.Set_Step_Info("Send ReSet command");
										g_theApp.LoadFtmCmdParameters(_T("ReSet"),csCmd,iDelay,iTimeout);
										lErrorCode = g_theApp.SendFtmCmd(csCmd,iDelay,iTimeout,csReturn,csErrMsg,csStatus,iRetry);

										if(lErrorCode != SUCCESS)
										{
											if(csReturn.Find("API status=",0) == -1)
												lErrorCode = CommReSetModeTimeout;	
											else
												lErrorCode = CommReSetModeFail;

											AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_ERROR_CODE, 
												FormatStr("ReSet Mode Fail, ErrorCode= %s", g_theApp.GetErrorString(lErrorCode)));
										}
									}
									//Get Initial power index
									csPowerIndex = FormatStr("%02X", st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].iPowerIndex);
								
									//int *currarrayindex_ptr = casPowerIndex;
									//for(int y=0;y<(sizeof(casPowerIndex)/sizeof(casPowerIndex[0]));y++)
									//{
									//	if(initialpowerindex == casPowerIndex[y])
									//		currarrayindex_ptr = currarrayindex_ptr+y;
									//}
									//if(initialpowerindex != *currarrayindex_ptr)
									//	lErrorCode = RKECAL_INITIAL_POWERINDEX_ERROR;
								
									//AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_COMMENT, 
									//		FormatStr("Initial Power-index = %.2X ", *currarrayindex_ptr));	
								
									if(lErrorCode == SUCCESS)
									{
										int iKcount = 1;
										int iMinflag = 0, iMaxflag = 0;
										do{
											g_theApp.Set_Step_Info(FormatStr("Power Calibration Test- %d", iKcount));
										
											g_theApp.Set_Step_Info(FormatStr("Add Delay Time 20 ms"));
											Sleep(20);


											if(lErrorCode == SUCCESS)
											{
												g_theApp.Set_Step_Info("Send ReSet command");
												g_theApp.LoadFtmCmdParameters(_T("ReSet"),csCmd,iDelay,iTimeout);
												lErrorCode = g_theApp.SendFtmCmd(csCmd,iDelay,iTimeout,csReturn,csErrMsg,csStatus,iRetry);

												if(lErrorCode != SUCCESS)
												{
													if(csReturn.Find("API status=",0) == -1)
														lErrorCode = CommReSetModeTimeout;	
													else
														lErrorCode = CommReSetModeFail;

													AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_ERROR_CODE, 
														FormatStr("ReSet Mode Fail, ErrorCode= %s", g_theApp.GetErrorString(lErrorCode)));
												}
											}

											if(lErrorCode == SUCCESS)
											{
												g_theApp.Set_Step_Info("Set Tx Mode command");
												g_theApp.LoadFtmCmdParameters(_T("SetTxModeOn"),csCmd,iDelay,iTimeout);
												csFreqIndex = FormatStr("%d", st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].iFreqIndex);
												csDataRateIndex = st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].csDataRateIndex;
												//csPowerIndex = FormatStr("%02X", st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].iPowerIndex);
												csCmd += " " + csFreqIndex + csDataRateIndex + " " + csPowerIndex + " 82 00 00 00 00";
												lErrorCode = g_theApp.SendFtmCmd(csCmd,iDelay,iTimeout,csReturn,csErrMsg,csStatus,iRetry);
			
												lErrorCode = SUCCESS;

											}

											g_theApp.Set_Step_Info(FormatStr("Add Delay Time %d ms", iDelayTime));
											Sleep(iDelayTime);

											// Set Sweep Single
											if(lErrorCode == SUCCESS)
												lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("DANalyse:IMMediate");

											// Wait-to-Continue
											if(lErrorCode == SUCCESS)
												lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("*WAI");

											// Get result
											csQuery_Result = "";
											if(lErrorCode == SUCCESS)
												lErrorCode = g_theApp.m_oRfUtility.GPIB_Query("DANalyse:DATA?", &csQuery_Result);

											// Switch to Free Run
											if(lErrorCode == SUCCESS && iEnableTrigger == 1)
											{
												lErrorCode = g_theApp.m_oRfUtility.GPIB_Send("DANalyse:FSK:TRIGger:SOURce IMM");
												Sleep(iDelayTime);
											}
										
											if(lErrorCode == SUCCESS)
											{
												if(!csQuery_Result.IsEmpty())
												{
													CArray<CString, CString> casTokenResult;
													ExtractToken(csQuery_Result, &casTokenResult, ",");
													int iResultSize = casTokenResult.GetSize();
													if(iResultSize == 15)
													{
														fCurrCarrPower = atof(casTokenResult[0]);
														fMaxCarrPower = atof(casTokenResult[1]);
														fMinCarrPower = atof(casTokenResult[2]);
														fCurrDeviation = atof(casTokenResult[3]); 
														fMaxDeviation = atof(casTokenResult[4]);
														fMinDeviation = atof(casTokenResult[5]);
														fCurrFskError = atof(casTokenResult[6]);
														fMaxFskError = atof(casTokenResult[7]);
														fMinFskError = atof(casTokenResult[8]);
														fCurrMagError = atof(casTokenResult[9]); 
														fMaxMagError = atof(casTokenResult[10]);
														fMinMagError = atof(casTokenResult[11]);
														fCurrCarrFreqOffset = atof(casTokenResult[12]);
														fMaxCarrFreqOffset = atof(casTokenResult[13]);
														fMinCarrFreqOffset = atof(casTokenResult[14]);
													}
													else
														lErrorCode = UNTRUSTED_MEASUREMENT;
												}
												else
													lErrorCode = INST_NO_MEASUREMENT_VALUE;
											}


											//CarrierPower
											if(lErrorCode == SUCCESS)
											{
												lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "CarrierPower/Enable", &sReturn);
												if(lErrorCode == SUCCESS)
													st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].s_RKE_CarrierPower.iEnable = atoi(sReturn);
											}
											if(st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].s_RKE_CarrierPower.iEnable)
											{
												if(lErrorCode == SUCCESS)
												{
													lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "CarrierPower/Target_power", &sReturn);
													if(lErrorCode == SUCCESS){
														st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].s_RKE_CarrierPower.fTarget_power = atof(sReturn);
														fTargetpower = atof(sReturn);
													}
												}
												if(lErrorCode == SUCCESS)
												{
													lErrorCode = g_theApp.m_oRfUtility.Get_Node_Str_And_Check(&mxpTest, "CarrierPower/Threshold_dB", &sReturn);
													if(lErrorCode == SUCCESS){
														st_RKE_SLTx.pSLItem->s_RKE_SLTxKeyItem[i].s_RKE_TxFreqItem[j].s_RKE_TxPowerItem[k].s_RKE_CarrierPower.fThreshold_dB = atof(sReturn);
														fThreshold = atof(sReturn);
													}
												}
												if(lErrorCode == SUCCESS)
												{
													AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_COMMENT, 
													FormatStr("CurrCarrPower= %.2f, Pathloss= %.2f, OutputCarrPower= %.2f", fCurrCarrPower, fPathloss, (fCurrCarrPower+fPathloss)));
													fCurrCarrPower += fPathloss;
												
													//output
													g_theApp.SendSpecResult(g_theApp.m_sItemName, FormatStr("KEY%d_Freq%d_Power%d__CarrierPower(dBm)", i, j, k),  FormatStr("%.2f", fCurrCarrPower),"","","",FormatStr("%.2s", csPowerIndex));
													g_theApp.SendSpecResult(g_theApp.m_sItemName, FormatStr("KEY%d_Freq%d_Power%d__Deviation(kHz)", i, j, k),  FormatStr("%.2f", fCurrDeviation),"","","");
													g_theApp.SendSpecResult(g_theApp.m_sItemName, FormatStr("KEY%d_Freq%d_Power%d__CarrFreqOffset(Hz)", i, j, k),  FormatStr("%.2f", fCurrCarrFreqOffset),"","","");

													csPowerIndex = FormatStr("%02X", iRFInputDac);
											    	AddLog(g_theApp.m_sLogFilePath, LOG_TYPE_COMMENT, 
													FormatStr("csPowerIndex = %.2s" , csPowerIndex));
												}
												/*if(lResult1 != SUCCESS && lResult == SUCCESS)
													lResult = lResult1;*/
											}
											iKcount++;
											if(iKcount > iExecuteCalibrationTime)
											{
												//lResult = RKE_TXPOWER_NOT_IN_RANGE;
											}
										}while( iKcount <= iExecuteCalibrationTime && lErrorCode == SUCCESS);

									}
									
									if(lResult != SUCCESS && lErrorCode == SUCCESS)
									{
										lErrorCode = lResult;
										lResult = SUCCESS;
										//lResult1 = SUCCESS;
										//lResult2 = SUCCESS;
										//lResult3 = SUCCESS;
										//lResult4 = SUCCESS;
										//lResult5 = SUCCESS;
									}
								
									iRetest++;
								} while(lErrorCode != SUCCESS && iRetest < 1);
							}
						}
					}// end for k
				}//end for x

				
			}	
		}// end for j
	}// end for i
	//send test item result message to mail slot
	///////////////////////////////////////
	//if(lTempError != SUCCESS && lErrorCode == SUCCESS)
	//	lErrorCode = lTempError;

	g_theApp.SendTestResult(g_theApp.m_sItemName, "", "", "", "", (lErrorCode == SUCCESS) ? true : false);

	return lErrorCode;
}