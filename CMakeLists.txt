cmake_minimum_required(VERSION 3.21)
project(AmazonChess_Traditional_Archive_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(Amazons)
include_directories(Amazons/Debug)

add_executable(AmazonChess_Traditional_Archive_master
        Amazons/Debug/Amazons.pch
        Amazons/AmazonsAI.cpp
        Amazons/AmazonsAI.h
        Amazons/AmazonsApp.cpp
        Amazons/AmazonsApp.h
        Amazons/AmazonsDoc.cpp
        Amazons/AmazonsDoc.h
        Amazons/AmazonsGameController.cpp
        Amazons/AmazonsGameController.h
        Amazons/AmazonsView.cpp
        Amazons/AmazonsView.h
        Amazons/APPMODUL.CPP
        Amazons/EvaluationFunction.cpp
        Amazons/EvaluationFunction.h
        Amazons/GameSettingDlg.cpp
        Amazons/GameSettingDlg.h
        Amazons/GlobalFunctions.cpp
        Amazons/GlobalFunctions.h
        Amazons/HistoryDlg.cpp
        Amazons/HistoryDlg.h
        Amazons/MainFrm.cpp
        Amazons/MainFrm.h
        Amazons/MoveGenerator.cpp
        Amazons/MoveGenerator.h
        Amazons/Name.h
        Amazons/resource.h
        Amazons/SearchEngine.cpp
        Amazons/SearchEngine.h
        Amazons/StdAfx.cpp
        Amazons/StdAfx.h
        Amazons/TipDlg.cpp
        Amazons/TipDlg.h)
