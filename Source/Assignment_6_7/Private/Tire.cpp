#include "Tire.h"

ATire::ATire()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	StaticMeshComp->SetMobility(EComponentMobility::Movable);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Assets/Scene_RoadsideConstruction/Assets/MS/3D/Ind_War_Handtruck_Metal_Worn_02/SM_Ind_War_Handtruck_Metal_Worn_02_B.SM_Ind_War_Handtruck_Metal_Worn_02_B"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialInstanceAsset(TEXT("/Game/Assets/Scene_RoadsideConstruction/Assets/MS/3D/Ind_War_Handtruck_Metal_Worn_02/MI_Ind_War_Handtruck_Metal_Worn_02.MI_Ind_War_Handtruck_Metal_Worn_02"));
	if (MaterialInstanceAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialInstanceAsset.Object);
	}
}

void ATire::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetActorScale3D(FVector(10.0f, 10.0f, 10.0f));
	SetActorRotation(FRotator(90.0f, 360.0f, -180.0f));
}

