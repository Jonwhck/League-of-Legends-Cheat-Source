#pragma once
//#define baseAddr (DWORD)GetModuleHandle(NULL)
//DWORD HiddenModule;

#define ORBWALKER_HOTKEY VK_SPACE
#define LASTHIT_HOTKEY 0x58
#define TARGET_GAMEVERSION "Version 11.23 [PUBLIC]"  // 
#define oRetAddr 0x3017211 // 0x5978A7		0x6E502		// find addr : ret // opcode : C3
//#define oDrawCircleRetAddr 0x6E4FF // 		// find addr : add esp, 28 ret // opcode : 83 C4 1C C3
#define oNetClient 0x3114F5C	 // 			8B 0D ? ? ? ? 85 C9 74 07 8B 01 6A 01 FF 50 08 8B // dword_[offset]
#define oChatClientPtr 0x30FC718  //  v   89 3D ? ? ? ? 8D B7 ? ? ? ? 6A 08 C7 47 ? ? ? ? ? // dword_[offset] // 8B 0D ? ? ? ? 6A 01 FF 74 24 08 // 74 1E 8B 09 > jump to loc first dword
#define oObjManager 0x186CD64 	 //	v		8B 0D ? ? ? ? 89 74 24 14 // dword_[offset]
#define oZoomClass 0x310124C 	 //		v		A3 ? ? ? ? 83 FA 10 72 32 // dword_[offset]
#define oViewMatrix 0x3132A30 // 	v 		B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E9 ? ? ? ? CC CC CC CC CC CC CC CC
#define oZoomAmount 0x28 // 
#define oGameInfo 0x2324A34 // 				A1 ? ? ? ? 83 78 08 02 0F 94 C0 // dword_[offset]
#define oHudInstance 0x186CD9C  	 //		v	8B 0D ? ? ? ? 6A 00 8B 49 34 E8 ? ? ? ? B0 // dword_[offset]
#define oRenderer 0x31358D0  	 // 	v			8B 15 ? ? ? ? 83 EC 08 F3 // dword_[offset]
#define oUnderMouseObject 0x30FC6EC   // v		8B 0D ? ? ? ? 89 0D // dword_[offset] // from 34E65C0 to 1C072C0 ?? //89 0D ? ? ? ? C7 41 ? ? ? ? ? 
//#define oD3DRenderer 0x180F208 // 			A1 ? ? ? ? 89 54 24 18 // dword_[offset]
#define oWorldToScreen 0xA28160  // 	v ?		8B 44 24 40 83 C4 08 F3 0F 10 44 24 ? // fn // 83 EC 10 56 E8 ?? ?? ?? ?? 8B 08
#define oLocalPlayer 0x3109D4C  //	v		A1 ?? ?? ?? ?? 85 C0 74 07 05 ?? ?? ?? ?? EB 02 33 C0 56 // dword_[offset]
#define oGameTime 0x3101314   // 	v			F3 0F 11 05 ? ? ? ? 8B 49 // dword_[offset]
#define oGetFirstObject 0x271AF0  //	v		8B 41 14 8B 51 18 // fn //  E8 ? ? ? ? 8B F0 85 F6 74 1E 66
#define oGetNextObject  0x2730C0  //	v		E8 ? ? ? ? 8B F0 85 F6 75 E4 // sub_[offset]
#define oGameVersion 0x562140 //			E8 ? ? ? ? 50 FF 36 8D 84 // sub_[offset]
#define oChat 0x3109E28  // 	v				FF D2 8B 0D ? ? ? ? 8A D8 // 66 89 47 6E DWORD_ SOTTO
#define oChatIsOpen 0x073C
#define oMenuGUI 0x3109D5C  // 	v			8B 0D ? ? ? ? 6A 00 E8 ? ? ? ? C7 // dword_[offset] // 8B 0D ? ? ? ? 6A 00 E8 ? ? ? ? C7 DWORD_SOPRA // 8B 44 24 14 C1 E8 04  DWORD SOTTO
//
#define oMissleList 0x30D9CDC
#define oMinionList 0x186CDFC //	v			A1 ? ? ? ? 57 33    // 0x18264B4 //// 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? EB 09		--->				 mov     ecx, dword_
#define oHeroList 0x186AB74 //	v				// // 89 44 24 18 A1 ? ? ? ? 53 55				---> first address;       mov     eax, dword_
#define oTurretList 0x30FD500		//v		// "towercautionRing_Minimal_Fountain_White"	---> 2 above;		 mov     dword_3325A48, esi

// FUNCTIONS
#define oCastSpell 0x5004C0 // 0x49D640				xref: ERROR: Client Tried to cast a spell from an invalid slot: %d.\n
#define oDrawCircle   0x4F9CD0 //	x		 	E8 ? ? ? ? 83 C4 1C 8B 7C 24 28 // sub_[offset] //TESTARE 33 C4 89 84 24 ? ? ? ? F3 0F 10 84 24 ? ? ? ? 8D 0C
#define oGetBasicAttack 0x14FFA0 // 	 	53 8B D9 B8 ? ? ? ? 8B 93 // fn
#define oGetAttackCastDelay 0x26E4F0  // v	83 EC 0C 53 8B 5C 24 14 8B CB 56 57 8B 03 FF 90 // fn
#define oGetAttackDelay 0x26E5F0  // 	v	E8 ? ? ? ? 8B 44 24 1C 83 C4 0C 8B CE // sub_[offset]
#define oGetPing 0x31FB50 // 				E8 ? ? ? ? 8B 4F 2C 85 C9 0F // sub_[offset] TESTARE 55 8B EC 83 EC 08 0F B6
//#define oPingInstance 0x350BC58 //			8B 0D ? ? ? ? 85 C9 74 07 8B 01 6A 01 FF 50 08 8B // dword_[offset]
#define oGetSpellState 0x4D9E10 // 			E8 ? ? ? ? 8B F8 8B CB 89 // sub_[offset]
#define oIsTargetable 0x372E00 //	x 		56 8B F1 E8 ? ? ? ? 84 C0 74 2E // fn // 56 8B F1 E8 ? ? ? ? 84 C0 74 2E 8D
#define oIsAlive 0x1416D0  // 	v			56 8B F1 8B 06 8B 80 ? ? ? ? FF D0 84 C0 74 19 // fn
#define oIsBaron 0x173DF0 //	x			E8 ? ? ? ? 84 C0 74 0A BB // sub_[offset]
#define oIsTurret 0x139DE0 // 	v			E8 ? ? ? ? 83 C4 04 84 C0 74 09 5F // sub_[offset]
#define oIsInhib 0x138B80 // 	x			E8 ? ? ? ? 83 C4 04 84 C0 74 38 // sub_[offset]
#define oIsHero 0x139BF0 // 	v			E8 ? ? ? ? 83 C4 04 84 C0 74 2B 57 // sub_[offset]
#define oIsMinion 0x139C30 // 	v			E8 ? ? ? ? 83 C4 04 84 C0 74 16 8B 0F // sub_[offset]
#define oIsDragon 0x1725B0 //  	x			E8 ? ? ? ? 33 DB 84 C0 0F 95 C3 8D 1C 5D ? ? ? ? E9 // sub_[offset]
#define oIsMissile 0x139C50 //	v	   		E8 ?? ?? ?? ?? 83 C4 04 84 C0 74 60 // sub_[offset]
//#define oIsNexus 0x1AB480 //				E8 ? ? ? ? 83 C4 04 84 C0 0F 95 C0 C3 CC 8A // sub_[offset]
#define oIsNotWall 0x9ABA50 // 	v			E8 ? ? ? ? 33 C9 83 C4 0C 84 // sub_[offset]
//#define oIsTroy 0x1A9BD0  // 				E8 ? ? ? ? 8B E8 83 C4 04 85 ED 0F 84 ? ? ? ? 6A 08 // go to sub_XXX then sub_[offset]
#define oIssueOrder 0x177870 // v			8B 44 24 20 C7 05 ?? ?? ?? ?? ?? ?? ?? ??// 81 EC ? ? ? ? 56 57 8B F9 C7 fn    81 EC ? ? ? ? 56 57 8B F9 C7 // 6A 0A E8 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? sub sotto
#define oPrintChat 0x588120  //	v			8B 0D ? ? ? ? 89 45 C0  // E8 ? ? ? ? 33 C0 5F C2 // sub_[offset] // TESTARE 83 EC 44 A1 ? ? ? ? 33 C5 89 45 FC 53 8B 5D 0C 56 8B // E8 ? ? ? ? FF 74 24 14 8D 4E 10 // E8 ? ? ? ? 6A 00 68 ? ? ? ? E8 ? ? ? ? 83 C4 04
#define oSendChat 0x5F49B0 //	v			A1 ? ? ? ? 56 6A FF // fn // E8 ? ? ? ? 8D 4C 24 04 C6 // sub_[offset] // FF 74 24 0C 05 ? ? ? ? FUNZIONE SOPRA SUB
#define oEndScreen 0x5E5540 // WTF? call with oMenuGUI				E8 ? ? ? ? 8B 0D ? ? ? ? E8 ? ? ? ? 84 C0 74 39 //E8 ? ? ? ? C6 45 2C 01
//#define oGetTimerExpiry 0x16C420 // 		E8 ? ? ? ? 51 D9 1C 24 E8 ? ? ? ? 8B // sub_[offset]
//#define oHealthBarPosition 0x5AB460 //		57 8B F9 6A 00 8B 47 18 // fn TESTARE 83 EC 28 53 55 56 57 8B F9 6A // 8B 4E 08 8D 54 24 04 52 SUB SOPRA
#define oBaseDrawPosition 0x1682F0 //		E8 ?? ?? ?? ?? EB ?? 8B 01 8B 40 // sub_[offset] TESTARE 30 44 14 10 42 3B D1 72 F0 8B 74 24 14 83 7C 24 ? ? 74
#define onProcessSpell 0x4f8840
#define OnCreateObject 0x27e1e0
#define OnDeleteObject 0xe86803
#define OnNewPath 0x27e4c0


//8B 0D C8 B5 56 03 FF  74 24 38 E8 40 6B 41 00

//CObject
#define oObjIndex 0x20
#define oObjTeam 0x4C
#define oObjName 0x6C //
#define oObjNetworkID 0xCC 
#define oObjPos 0x1F4 //
#define oObjMissileSpellCast 0x250
#define oObjVisibility 0x28C
#define oObjHealth 0xDB4 //
#define oObjMaxHealth 0xDC4
#define oObjMana 0x298
#define oObjInvulnerable 0x3EC
#define oObjTargetable 0xD1C 
#define oObjRecallState 0xD90
#define oObjAbilityHaste 0x10F4
#define oObjLethality 0x11DC
#define oObjArmor 0x12E4
#define oObjBonusArmor 0x12e8
#define oObjMagicRes 0x12D0
#define oObjBonusMagicRes 0x12D0
#define oObjBaseAtk 0x12BC
#define oObjBonusAtk 0x1234
#define oObjCrit  0x12C4
#define oObjCritMulti 0x12B4
#define oObjAbilityPower 0x1228
#define oObjAtkSpeedMulti 0x129C
#define oObjMagicPen  0x11C0
#define oObjMagicPenMulti 0x11C8 // 1 when no magi pene is applied
#define oObjAdditionalApMulti 0x122 //when rabadon = 0.35
#define oObjMoveSpeed 0x12FC
#define oObjAtkRange 0x1304	
#define oObjBuffMgr 0x2178

#define oObjChampionName 0x2DA4 
#define oObjLevel 0x33DC
//#define oObjSourceIndex 0x290
#define oObjDirection 0x1B88

#define oObjTransformation 0x2f80

#define oMissileSpellInfo 0x258
#define oMissileSourceIndex 0x2B4
#define oMissileTargetIndex 0x310
#define oMissileStartPos 0x2F4
#define oMissileEndPos 0x300

#define oObjBuffManager 0x21A4
#define oBuffManagerEntriesArray 0x10
#define oBuffEntryBuff 0x8
#define oBuffEntryBuffStartTime 0xC
#define oBuffEntryBuffEndTime 0x10
#define oBuffEntryBuffCount 0x74
#define oBuffName 0x8
#define oBuffEntryBuffNodeStart 0x20
#define oBuffEntryBuffNodeCurrent 0x24

#define oObjSpellBook 0x2370 // 0F 84 ? ? ? ? 8D 88 ? ? ? ? 89 8D ? ? ? ? 
#define oSpellBookActiveSpellCast 0x20
#define oSpellBookCastableMask 0x38
#define oSpellBookSpellSlots 0x488

#define oSpellCastSpellInfo 0x8
#define oSpellCastStartTime 0x14c
#define oSpellCastCastTime 0xcc
#define oSpellCastStart 0x84
#define oSpellCastEnd 0x90
#define oSpellCastSrcIdx 0x6C
#define oSpellCastDestIdx 0xC0

#define oObjItemList 0x33A0
#define oItemListItem 0xC
#define oItemActiveName 0x10
#define oItemCharges 0x24
#define oItemInfo 0x20
#define oItemInfoId 0x68

#define oRendererWidth 0xC
#define oRendererHeight 0x10

#define oSpellSlotLevel 0x20
#define oSpellSlotTime 0x28
#define oSpellSlotCharges 0x58
#define oSpellSlotTimeCharge 0x64
#define oSpellSlotValue 0x94
#define oSpellSlotCooldownExpire 0x28
#define oSpellSlotRemainingCharge 0x58
#define oSpellSlotIsActive 0x74
#define oSpellSlotDamage 0x94
#define oSpellSlotCooldown 0xA4
#define oSpellSlotSpellInfo 0x13C //144?

#define oSpellInfoSpellData  0x44 //			
#define oSpellDataSpellName 0x6C
#define oSpellDataMissileName 0x6C
#define oSpellDataManaArray 0x524

////#define oSpellSlotSpellInfo  0x13C //			
//#define oSpellInfoSpellData  0x44 //			
//#define oSpellDataSpellName 0x6C
//#define oSpellDataMissileName 0x6C
//#define oSpellDataManaArray 0x524



//
#define objectArray 0x14

//buff
#define O_BUFFMGR_BUFFNAME 0x08
#define O_BUFFMGR_STARTTIME 0xC
#define O_BUFFMGR_ENDTIME 0x10
#define O_BUFFMGR_flBUFFCOUNT 0x130 
#define O_BUFFMGR_iBUFFCOUNT 0x74 
#define oBuffType 0x4
#define oBuffCountAlt 0x24
#define oBuffCountAlt2 0x20

//AIMANAGER
#define oAIMGR_TargetPos  0x10
#define oAIMGR_IsMoving  0x1c0
#define oAIMGR_IsDashing  0x214
#define oAIMGR_NavBegin  0x1cc
#define oAIMGR_NavEnd  0x224
#define oAIMGR_ServerPos  0x2e4
#define oAIMGR_Velocity  0x2f0
//
//inline bool checkIfLogExistCreateIfNot() {
//	if (FILE* file = fopen("log.txt", "r")) {
//		fclose(file);
//		return true;
//	}
//	else {
//		ofstream MyFile("log.txt");
//		MyFile.close();
//	}
//	return true;
//}
//
//inline void writeDataToFile(string name, DWORD address) {
//	checkIfLogExistCreateIfNot();
//	FILE* logfile;
//	// _CRT_SECURE_NO_DEPRECATE;
//	if ((logfile = fopen("log.txt", "a+")) != NULL)
//	{
//		fprintf(logfile, (name + " : " + hexify<DWORD>(address) + "\n").c_str());
//		fclose(logfile);
//	}
//}
//
//template< typename T >
//std::string hexify(T i)
//{
//	std::stringbuf buf;
//	std::ostream os(&buf);
//
//
//	os << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
//		<< std::hex << i;
//
//	return buf.str().c_str();
//}
//
//#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
//
//#define INRANGE(x,a,b)    (x >= a && x <= b) 
//#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
//#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
//inline DWORD FindPatternV2(std::string moduleName, std::string Mask)
//{
//	const char* pat = Mask.c_str();
//	DWORD firstMatch = 0;
//	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
//	MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
//	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
//
//	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
//	{
//		if (!*pat)
//			return firstMatch;
//
//		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
//		{
//			if (!firstMatch)
//				firstMatch = pCur;
//
//			if (!pat[2])
//				return firstMatch;
//
//			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
//				pat += 3;
//
//			else
//				pat += 2; //one ?
//		}
//		else
//		{
//			pat = Mask.c_str();
//			firstMatch = 0;
//		}
//	}
//	return NULL;
//}