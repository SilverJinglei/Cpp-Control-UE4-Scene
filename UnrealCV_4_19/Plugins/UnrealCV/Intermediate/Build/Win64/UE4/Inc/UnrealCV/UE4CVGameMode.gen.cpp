// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/UnrealCVPrivate.h"
#include "Public/UE4CVGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUE4CVGameMode() {}
// Cross Module References
	UNREALCV_API UClass* Z_Construct_UClass_AUE4CVGameMode_NoRegister();
	UNREALCV_API UClass* Z_Construct_UClass_AUE4CVGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_UnrealCV();
	UNREALCV_API UClass* Z_Construct_UClass_AUE4CVPawn_NoRegister();
	UNREALCV_API UClass* Z_Construct_UClass_AUE4CVPawn();
	ENGINE_API UClass* Z_Construct_UClass_ADefaultPawn();
	UNREALCV_API UClass* Z_Construct_UClass_AUE4CVCharacter_NoRegister();
	UNREALCV_API UClass* Z_Construct_UClass_AUE4CVCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
// End Cross Module References
	void AUE4CVGameMode::StaticRegisterNativesAUE4CVGameMode()
	{
	}
	UClass* Z_Construct_UClass_AUE4CVGameMode_NoRegister()
	{
		return AUE4CVGameMode::StaticClass();
	}
	UClass* Z_Construct_UClass_AUE4CVGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AGameMode,
				(UObject* (*)())Z_Construct_UPackage__Script_UnrealCV,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
				{ "IncludePath", "UE4CVGameMode.h" },
				{ "ModuleRelativePath", "Public/UE4CVGameMode.h" },
				{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AUE4CVGameMode>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AUE4CVGameMode::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x0090028Cu,
				nullptr, 0,
				nullptr, 0,
				"Game",
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AUE4CVGameMode, 3195531336);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AUE4CVGameMode(Z_Construct_UClass_AUE4CVGameMode, &AUE4CVGameMode::StaticClass, TEXT("/Script/UnrealCV"), TEXT("AUE4CVGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUE4CVGameMode);
	void AUE4CVPawn::StaticRegisterNativesAUE4CVPawn()
	{
	}
	UClass* Z_Construct_UClass_AUE4CVPawn_NoRegister()
	{
		return AUE4CVPawn::StaticClass();
	}
	UClass* Z_Construct_UClass_AUE4CVPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_ADefaultPawn,
				(UObject* (*)())Z_Construct_UPackage__Script_UnrealCV,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Navigation" },
				{ "IncludePath", "UE4CVGameMode.h" },
				{ "ModuleRelativePath", "Public/UE4CVGameMode.h" },
				{ "ToolTip", "UE4CVPawn can move freely in the 3D space" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AUE4CVPawn>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AUE4CVPawn::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
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
	IMPLEMENT_CLASS(AUE4CVPawn, 1879688291);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AUE4CVPawn(Z_Construct_UClass_AUE4CVPawn, &AUE4CVPawn::StaticClass, TEXT("/Script/UnrealCV"), TEXT("AUE4CVPawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUE4CVPawn);
	void AUE4CVCharacter::StaticRegisterNativesAUE4CVCharacter()
	{
	}
	UClass* Z_Construct_UClass_AUE4CVCharacter_NoRegister()
	{
		return AUE4CVCharacter::StaticClass();
	}
	UClass* Z_Construct_UClass_AUE4CVCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_ACharacter,
				(UObject* (*)())Z_Construct_UPackage__Script_UnrealCV,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Navigation" },
				{ "IncludePath", "UE4CVGameMode.h" },
				{ "ModuleRelativePath", "Public/UE4CVGameMode.h" },
				{ "ToolTip", "UE4CVCharacter acts like a walking human" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AUE4CVCharacter>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AUE4CVCharacter::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
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
	IMPLEMENT_CLASS(AUE4CVCharacter, 2581967766);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AUE4CVCharacter(Z_Construct_UClass_AUE4CVCharacter, &AUE4CVCharacter::StaticClass, TEXT("/Script/UnrealCV"), TEXT("AUE4CVCharacter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUE4CVCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
