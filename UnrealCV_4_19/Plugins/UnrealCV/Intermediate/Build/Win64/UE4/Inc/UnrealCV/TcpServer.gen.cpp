// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/UnrealCVPrivate.h"
#include "Public/TcpServer.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTcpServer() {}
// Cross Module References
	UNREALCV_API UClass* Z_Construct_UClass_UNetworkManager_NoRegister();
	UNREALCV_API UClass* Z_Construct_UClass_UNetworkManager();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_UnrealCV();
// End Cross Module References
	void UNetworkManager::StaticRegisterNativesUNetworkManager()
	{
	}
	UClass* Z_Construct_UClass_UNetworkManager_NoRegister()
	{
		return UNetworkManager::StaticClass();
	}
	UClass* Z_Construct_UClass_UNetworkManager()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UObject,
				(UObject* (*)())Z_Construct_UPackage__Script_UnrealCV,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "TcpServer.h" },
				{ "ModuleRelativePath", "Public/TcpServer.h" },
				{ "ToolTip", "Server to send and receive message" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<UNetworkManager>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&UNetworkManager::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00100080u,
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
	IMPLEMENT_CLASS(UNetworkManager, 3799643413);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNetworkManager(Z_Construct_UClass_UNetworkManager, &UNetworkManager::StaticClass, TEXT("/Script/UnrealCV"), TEXT("UNetworkManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNetworkManager);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
