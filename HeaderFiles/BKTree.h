///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// Project : Assignment_1
// File : 
///////////////////////////////////

#pragma once

#include "EntryList.h"
#include "core.h"
#include "DataStructs.h"

BKTree BKT_Create(MatchType );
BKTreeNode BKT_CreateNode(Entry *);
BKTreeNode BKT_Insert(const BKTree , Entry *);
BKTreeNode BKT_InsertNode(const BKTree , const BKTreeNode , Entry *);
List *BKT_Search(const BKTree , const char *, const int );
int BKT_Destroy(BKTree );
int BKT_DestroyNode(BKTreeNode );