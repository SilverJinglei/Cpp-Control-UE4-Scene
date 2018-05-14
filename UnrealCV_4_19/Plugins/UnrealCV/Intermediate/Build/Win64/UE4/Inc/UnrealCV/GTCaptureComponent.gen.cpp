// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/UnrealCVPrivate.h"
#include "Public/GTCaptureComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGTCaptureComponent() {}
// Cross Module References
	UNREALCV_API UClass* Z_Construct_UClass_UGTCaptureComponent_NoRegister();
	UNREALCV_API UClass* Z_Construct_UClass_UGTCaptureComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	UPackage* Z_Construct_UPackage__Script_UnrealCV();
// End Cross Module References
	void UGTCaptureComponent::StaticRegisterNativesUGTCaptureComponent()
	{
	}
	UClass* Z_Construct_UClass_UGTCaptureComponent_NoRegister()
	{
		return UGTCaptureComponent::StaticClass();
	}
	UClass* Z_Construct_UClass_UGTCaptureComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_USceneComponent,
				(UObject* (*)())Z_Construct_UPackage__Script_UnrealCV,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Trigger PhysicsVolume" },
				{ "IncludePath", "GTCaptureComponent.h" },
				{ "ModuleRelativePath", "Public/GTCaptureComponent.h" },
				{ "ToolTip", "Use USceneCaptureComponent2D to export information from the scene.\nThis class needs to be tickable to update the rotation of the USceneCaptureComponent2D" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<UGTCaptureComponent>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&UGTCaptureComponent::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00B00080u,
				nullptr, 0,
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGTCaptureComponent, 3373820323);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGTCaptureComponent(Z_Construct_UClass_UGTCaptureComponent, &UGTCaptureComponent::StaticClass, TEXT("/Script/UnrealCV"), TEXT("UGTCaptureComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGTCaptureComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
