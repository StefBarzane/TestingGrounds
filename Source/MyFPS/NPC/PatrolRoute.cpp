// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFPS.h"
#include "PatrolRoute.h"

TArray<AActor*> UPatrolRoute::GetPatrolPoints() const
{
	return PatrolPoints;
}
