// This file is generated, don't edit it!!

#if !defined(ERRHEADER_XMLExcepts)
#define ERRHEADER_XMLExcepts

class XMLExcepts
{
public :
    enum Codes
    {
        NoError                            = 0
      , W_LowBounds                        = 1
      , Scan_CouldNotOpenSource_Warning    = 2
      , W_HighBounds                       = 3
      , F_LowBounds                        = 4
      , Array_BadIndex                     = 5
      , Array_BadNewSize                   = 6
      , AttrList_BadIndex                  = 7
      , AttDef_BadAttType                  = 8
      , AttDef_BadDefAttType               = 9
      , Bitset_BadIndex                    = 10
      , Bitset_NotEqualSize                = 11
      , BufMgr_NoMoreBuffers               = 12
      , BufMgr_BufferNotInPool             = 13
      , CPtr_PointerIsZero                 = 14
      , CM_BinOpHadUnaryType               = 15
      , CM_MustBeMixedOrChildren           = 16
      , CM_NoPCDATAHere                    = 17
      , CM_NotValidForSpecType             = 18
      , CM_UnaryOpHadBinType               = 19
      , CM_UnknownCMType                   = 20
      , CM_UnknownCMSpecType               = 21
      , CM_NoParentCSN                     = 22
      , CM_NotValidSpecTypeForNode         = 23
      , DTD_UnknownCreateReason            = 24
      , ElemStack_EmptyStack               = 25
      , ElemStack_BadIndex                 = 26
      , ElemStack_StackUnderflow           = 27
      , ElemStack_NoParentPushed           = 28
      , Enum_NoMoreElements                = 29
      , File_CouldNotOpenFile              = 30
      , File_CouldNotGetCurPos             = 31
      , File_CouldNotCloseFile             = 32
      , File_CouldNotSeekToEnd             = 33
      , File_CouldNotSeekToPos             = 34
      , File_CouldNotDupHandle             = 35
      , File_CouldNotReadFromFile          = 36
      , File_CouldNotResetFile             = 37
      , File_CouldNotGetSize               = 38
      , File_CouldNotGetBasePathName       = 39
      , File_BasePathUnderflow             = 40
      , Gen_ParseInProgress                = 41
      , Gen_NoDTDValidator                 = 42
      , Gen_CouldNotOpenDTD                = 43
      , Gen_CouldNotOpenExtEntity          = 44
      , Gen_UnexpectedEOF                  = 45
      , HshTbl_ZeroModulus                 = 46
      , HshTbl_BadHashFromKey              = 47
      , HshTbl_NoSuchKeyExists             = 48
      , Mutex_CouldNotCreate               = 49
      , Mutex_CouldNotClose                = 50
      , Mutex_CouldNotLock                 = 51
      , Mutex_CouldNotUnlock               = 52
      , Mutex_CouldNotDestroy              = 53
      , NetAcc_InternalError               = 54
      , NetAcc_InitFailed                  = 55
      , NetAcc_TargetResolution            = 56
      , NetAcc_CreateSocket                = 57
      , NetAcc_ConnSocket                  = 58
      , NetAcc_WriteSocket                 = 59
      , NetAcc_ReadSocket                  = 60
      , Pool_ElemAlreadyExists             = 61
      , Pool_BadHashFromKey                = 62
      , Pool_InvalidId                     = 63
      , Pool_ZeroModulus                   = 64
      , RdrMgr_ReaderIdNotFound            = 65
      , Reader_BadAutoEncoding             = 66
      , Reader_CouldNotDecodeFirstLine     = 67
      , Reader_EOIInMultiSeq               = 68
      , Reader_SrcOfsNotSupported          = 69
      , Reader_EncodingStrRequired         = 70
      , Scan_CouldNotOpenSource            = 71
      , Scan_UnbalancedStartEnd            = 72
      , Scan_BadPScanToken                 = 73
      , Stack_BadIndex                     = 74
      , Stack_EmptyStack                   = 75
      , Str_ZeroSizedTargetBuf             = 76
      , Str_UnknownRadix                   = 77
      , Str_TargetBufTooSmall              = 78
      , Str_StartIndexPastEnd              = 79
      , Str_ConvertOverflow                = 80
      , Strm_StdErrWriteFailure            = 81
      , Strm_StdOutWriteFailure            = 82
      , Strm_ConWriteFailure               = 83
      , StrPool_IllegalId                  = 84
      , Trans_CouldNotCreateDefCvtr        = 85
      , Trans_InvalidSizeReq               = 86
      , Trans_Unrepresentable              = 87
      , Trans_NotValidForEncoding          = 88
      , Trans_BadBlockSize                 = 89
      , Trans_BadSrcSeq                    = 90
      , Trans_BadSrcCP                     = 91
      , Trans_BadTrailingSurrogate         = 92
      , Trans_CantCreateCvtrFor            = 93
      , URL_MalformedURL                   = 94
      , URL_UnsupportedProto               = 95
      , URL_UnsupportedProto1              = 96
      , URL_OnlyLocalHost                  = 97
      , URL_NoProtocolPresent              = 98
      , URL_ExpectingTwoSlashes            = 99
      , URL_IncorrectEscapedCharRef        = 100
      , URL_UnterminatedHostComponent      = 101
      , URL_RelativeBaseURL                = 102
      , URL_BaseUnderflow                  = 103
      , URL_BadPortField                   = 104
      , Vector_BadIndex                    = 105
      , Val_InvalidElemId                  = 106
      , Val_CantHaveIntSS                  = 107
      , XMLRec_UnknownEncoding             = 108
      , Parser_Parse1                      = 109
      , Parser_Parse2                      = 110
      , Parser_Next1                       = 111
      , Parser_Next2                       = 112
      , Parser_Next3                       = 113
      , Parser_Next4                       = 114
      , Parser_Factor1                     = 115
      , Parser_Factor2                     = 116
      , Parser_Factor3                     = 117
      , Parser_Factor4                     = 118
      , Parser_Factor5                     = 119
      , Parser_Factor6                     = 120
      , Parser_Atom1                       = 121
      , Parser_Atom2                       = 122
      , Parser_Atom3                       = 123
      , Parser_Atom4                       = 124
      , Parser_Atom5                       = 125
      , Parser_CC1                         = 126
      , Parser_CC2                         = 127
      , Parser_CC3                         = 128
      , Parser_CC4                         = 129
      , Parser_CC5                         = 130
      , Parser_CC6                         = 131
      , Parser_CC7                         = 132
      , Parser_Ope1                        = 133
      , Parser_Ope2                        = 134
      , Parser_Ope3                        = 135
      , Parser_Descape1                    = 136
      , Parser_Descape2                    = 137
      , Parser_Descape3                    = 138
      , Parser_Descape4                    = 139
      , Parser_Descape5                    = 140
      , Parser_Process1                    = 141
      , Parser_Process2                    = 142
      , Gen_NoSchemaValidator              = 143
      , XUTIL_UnCopyableNodeType           = 144
      , SubGrpComparator_NGR               = 145
      , FACET_Invalid_Len                  = 146
      , FACET_Invalid_maxLen               = 147
      , FACET_Invalid_minLen               = 148
      , FACET_NonNeg_Len                   = 149
      , FACET_NonNeg_maxLen                = 150
      , FACET_NonNeg_minLen                = 151
      , FACET_Len_maxLen                   = 152
      , FACET_Len_minLen                   = 153
      , FACET_maxLen_minLen                = 154
      , FACET_bool_Pattern                 = 155
      , FACET_Invalid_Tag                  = 156
      , FACET_Len_baseLen                  = 157
      , FACET_minLen_baseminLen            = 158
      , FACET_minLen_basemaxLen            = 159
      , FACET_maxLen_basemaxLen            = 160
      , FACET_maxLen_baseminLen            = 161
      , FACET_enum_base                    = 162
      , FACET_Invalid_WS                   = 163
      , FACET_WS_collapse                  = 164
      , FACET_WS_replace                   = 165
      , FACET_Invalid_MaxIncl              = 166
      , FACET_Invalid_MaxExcl              = 167
      , FACET_Invalid_MinIncl              = 168
      , FACET_Invalid_MinExcl              = 169
      , FACET_Invalid_TotalDigit           = 170
      , FACET_Invalid_FractDigit           = 171
      , FACET_NonNeg_TotalDigit            = 172
      , FACET_NonNeg_FractDigit            = 173
      , FACET_max_Incl_Excl                = 174
      , FACET_min_Incl_Excl                = 175
      , FACET_maxExcl_minExcl              = 176
      , FACET_maxExcl_minIncl              = 177
      , FACET_maxIncl_minExcl              = 178
      , FACET_maxIncl_minIncl              = 179
      , FACET_TotDigit_FractDigit          = 180
      , FACET_maxIncl_base_maxExcl         = 181
      , FACET_maxIncl_base_maxIncl         = 182
      , FACET_maxIncl_base_minIncl         = 183
      , FACET_maxIncl_base_minExcl         = 184
      , FACET_maxExcl_base_maxExcl         = 185
      , FACET_maxExcl_base_maxIncl         = 186
      , FACET_maxExcl_base_minIncl         = 187
      , FACET_maxExcl_base_minExcl         = 188
      , FACET_minExcl_base_maxExcl         = 189
      , FACET_minExcl_base_maxIncl         = 190
      , FACET_minExcl_base_minIncl         = 191
      , FACET_minExcl_base_minExcl         = 192
      , FACET_minIncl_base_maxExcl         = 193
      , FACET_minIncl_base_maxIncl         = 194
      , FACET_minIncl_base_minIncl         = 195
      , FACET_minIncl_base_minExcl         = 196
      , FACET_maxIncl_notFromBase          = 197
      , FACET_maxExcl_notFromBase          = 198
      , FACET_minIncl_notFromBase          = 199
      , FACET_minExcl_notFromBase          = 200
      , FACET_totalDigit_base_totalDigit   = 201
      , FACET_fractDigit_base_totalDigit   = 202
      , FACET_fractDigit_base_fractDigit   = 203
      , FACET_maxIncl_base_fixed           = 204
      , FACET_maxExcl_base_fixed           = 205
      , FACET_minIncl_base_fixed           = 206
      , FACET_minExcl_base_fixed           = 207
      , FACET_totalDigit_base_fixed        = 208
      , FACET_fractDigit_base_fixed        = 209
      , FACET_maxLen_base_fixed            = 210
      , FACET_minLen_base_fixed            = 211
      , FACET_len_base_fixed               = 212
      , FACET_whitespace_base_fixed        = 213
      , FACET_internalError_fixed          = 214
      , FACET_List_Null_baseValidator      = 215
      , FACET_Union_Null_memberTypeValidators   = 216
      , FACET_Union_Null_baseValidator     = 217
      , FACET_Union_invalid_baseValidatorType   = 218
      , VALUE_NotMatch_Pattern             = 219
      , VALUE_Not_Base64                   = 220
      , VALUE_Not_HexBin                   = 221
      , VALUE_GT_maxLen                    = 222
      , VALUE_LT_minLen                    = 223
      , VALUE_NE_Len                       = 224
      , VALUE_NotIn_Enumeration            = 225
      , VALUE_exceed_totalDigit            = 226
      , VALUE_exceed_fractDigit            = 227
      , VALUE_exceed_maxIncl               = 228
      , VALUE_exceed_maxExcl               = 229
      , VALUE_exceed_minIncl               = 230
      , VALUE_exceed_minExcl               = 231
      , VALUE_WS_replaced                  = 232
      , VALUE_WS_collapsed                 = 233
      , VALUE_Invalid_NCName               = 234
      , VALUE_Invalid_Name                 = 235
      , VALUE_ID_Not_Unique                = 236
      , VALUE_ENTITY_Invalid               = 237
      , VALUE_QName_Invalid                = 238
      , VALUE_NOTATION_Invalid             = 239
      , VALUE_no_match_memberType          = 240
      , VALUE_URI_Malformed                = 241
      , XMLNUM_emptyString                 = 242
      , XMLNUM_WSString                    = 243
      , XMLNUM_2ManyDecPoint               = 244
      , XMLNUM_Inv_chars                   = 245
      , XMLNUM_null_ptr                    = 246
      , XMLNUM_URI_Component_Empty         = 247
      , XMLNUM_URI_Component_for_GenURI_Only   = 248
      , XMLNUM_URI_Component_Invalid_EscapeSequence   = 249
      , XMLNUM_URI_Component_Invalid_Char   = 250
      , XMLNUM_URI_Component_Set_Null      = 251
      , XMLNUM_URI_Component_Not_Conformant   = 252
      , XMLNUM_URI_No_Scheme               = 253
      , XMLNUM_URI_NullHost                = 254
      , XMLNUM_URI_NullPath                = 255
      , XMLNUM_URI_Component_inPath        = 256
      , XMLNUM_URI_PortNo_Invalid          = 257
      , XMLNUM_DBL_FLT_maxNeg              = 258
      , XMLNUM_DBL_FLT_maxPos              = 259
      , XMLNUM_DBL_FLT_minNegPos           = 260
      , XMLNUM_DBL_FLT_InvalidType         = 261
      , XMLNUM_DBL_FLT_No_Exponent         = 262
      , Regex_Result_Not_Set               = 263
      , Regex_CompactRangesError           = 264
      , Regex_MergeRangesTypeMismatch      = 265
      , Regex_SubtractRangesError          = 266
      , Regex_IntersectRangesError         = 267
      , Regex_ComplementRangesInvalidArg   = 268
      , Regex_InvalidCategoryName          = 269
      , Regex_KeywordNotFound              = 270
      , Regex_BadRefNo                     = 271
      , Regex_UnknownOption                = 272
      , Regex_UnknownTokenType             = 273
      , Regex_RangeTokenGetError           = 274
      , Regex_NotSupported                 = 275
      , Regex_InvalidChildIndex            = 276
      , Regex_InvalidQuantifier            = 277
      , NEL_RepeatedCalls                  = 278
      , RethrowError                       = 279
      , Out_Of_Memory                      = 280
      , DV_InvalidOperation                = 281
      , XPath_NoAttrSelector               = 282
      , XPath_NoUnionAtStart               = 283
      , XPath_NoMultipleUnion              = 284
      , XPath_MissingAttr                  = 285
      , XPath_ExpectedToken1               = 286
      , XPath_PrefixNoURI                  = 287
      , XPath_NoDoubleColon                = 288
      , XPath_ExpectedStep1                = 289
      , XPath_ExpectedStep2                = 290
      , XPath_ExpectedStep3                = 291
      , XPath_NoForwardSlash               = 292
      , XPath_NoDoubleForwardSlash         = 293
      , XPath_NoForwardSlashAtStart        = 294
      , XPath_NoSelectionOfRoot            = 295
      , XPath_EmptyExpr                    = 296
      , XPath_NoUnionAtEnd                 = 297
      , XPath_InvalidChar                  = 298
      , XPath_TokenNotSupported            = 299
      , XPath_FindSolution                 = 300
      , DateTime_Assert_Buffer_Fail        = 301
      , DateTime_dt_missingT               = 302
      , DateTime_gDay_invalid              = 303
      , DateTime_gMth_invalid              = 304
      , DateTime_gMthDay_invalid           = 305
      , DateTime_dur_Start_dashP           = 306
      , DateTime_dur_noP                   = 307
      , DateTime_dur_DashNotFirst          = 308
      , DateTime_dur_inv_b4T               = 309
      , DateTime_dur_NoTimeAfterT          = 310
      , DateTime_dur_NoElementAtAll        = 311
      , DateTime_date_incomplete           = 312
      , DateTime_date_invalid              = 313
      , DateTime_time_incomplete           = 314
      , DateTime_time_invalid              = 315
      , DateTime_ms_noDigit                = 316
      , DateTime_ym_incomplete             = 317
      , DateTime_ym_invalid                = 318
      , DateTime_year_tooShort             = 319
      , DateTime_year_leadingZero          = 320
      , DateTime_ym_noMonth                = 321
      , DateTime_tz_noUTCsign              = 322
      , DateTime_tz_stuffAfterZ            = 323
      , DateTime_tz_invalid                = 324
      , DateTime_year_zero                 = 325
      , DateTime_mth_invalid               = 326
      , DateTime_day_invalid               = 327
      , DateTime_hour_invalid              = 328
      , DateTime_min_invalid               = 329
      , DateTime_second_invalid            = 330
      , DateTime_tz_hh_invalid             = 331
      , PD_NSCompat1                       = 332
      , PD_OccurRangeE                     = 333
      , PD_NameTypeOK1                     = 334
      , PD_NameTypeOK2                     = 335
      , PD_NameTypeOK3                     = 336
      , PD_NameTypeOK4                     = 337
      , PD_NameTypeOK5                     = 338
      , PD_NameTypeOK6                     = 339
      , PD_NameTypeOK7                     = 340
      , PD_RecurseAsIfGroup                = 341
      , PD_Recurse1                        = 342
      , PD_Recurse2                        = 343
      , PD_ForbiddenRes1                   = 344
      , PD_ForbiddenRes2                   = 345
      , PD_ForbiddenRes3                   = 346
      , PD_ForbiddenRes4                   = 347
      , PD_NSSubset1                       = 348
      , PD_NSSubset2                       = 349
      , PD_NSRecurseCheckCardinality1      = 350
      , PD_RecurseUnordered                = 351
      , PD_MapAndSum                       = 352
      , PD_InvalidContentType              = 353
      , NodeIDMap_GrowErr                  = 354
      , F_HighBounds                       = 355
      , E_LowBounds                        = 356
      , E_HighBounds                       = 357
    };

};
#endif

