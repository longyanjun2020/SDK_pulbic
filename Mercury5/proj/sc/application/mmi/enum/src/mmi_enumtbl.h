#ifndef __MMI_ENUMTBL_H__
#define __MMI_ENUMTBL_H__

#define DEFINE_TENUM(_Enum_) (_Enum_::typeid)

ref struct MAE_Enumerations abstract sealed
{
	initonly static array<System::Type^>^ Item =
	{
		DEFINE_TENUM(MAE_CoreClass_e),
		DEFINE_TENUM(MAE_BasicClass_e),
		DEFINE_TENUM(MAE_ModelClass_e),
		DEFINE_TENUM(MAE_WidgetClass_e),
		DEFINE_TENUM(MAE_ServiceClass_e),
		DEFINE_TENUM(MAE_AppletClass_e),
	};
};

#endif //  __MMI_ENUMTBL_H__
