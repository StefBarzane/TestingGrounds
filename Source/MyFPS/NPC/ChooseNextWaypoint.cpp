// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFPS.h"
#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//TODO: protection

	//get patrol points
	AAIController* AIController = OwnerComp.GetAIOwner();
	//if (!ensure(AIController)) { return EBTNodeResult::Failed; }

	APawn* ControlledPawn = AIController->GetPawn();
	//if (!ensure(ControlledPawn)) { return EBTNodeResult::Failed; }

	auto PatrolRouteComp = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	//if (!ensure(PatrolRouteComp)) { EBTNodeResult::Failed; }
	
	auto PatrolPoints = PatrolRouteComp->GetPatrolPoints();
	//if (!ensure(PatrolPoints.Num() > 0)) { EBTNodeResult::Failed; }

	//set next waypoint
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto index = BlackBoardComp->GetValueAsInt(indexKey.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(nextWaypointKey.SelectedKeyName, PatrolPoints[index]);

	//cycle index
	auto NextIndex = (index + 1) % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(indexKey.SelectedKeyName, NextIndex);

	///UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), index);
	return EBTNodeResult::Succeeded;
}
