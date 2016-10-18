cmake_minimum_required(VERSION 3.6)

# Project settings
project(ArmSTALKER VERSION 0.0.0.1)

# Qt Libraries
set(QT_LIBRARIES_REQUIRED Core Widgets Gui Network)

# External Libraries
set(EXTERNAL_LIBRARIES version)

# Sources
#file(GLOB_RECURSE SOURCE_FILES *.cpp)
set(SOURCE_FILES
        src/launcher/base/starter/main.cpp
        # Core
        src/core/base/core/BaseCore.h
        src/core/base/presenter/BasePresenter.h
        src/core/base/view/BaseView.h
        src/core/base/logger/Logger.h
        src/core/base/logger/Logger.cpp
        # Launcher
        src/launcher/base/presenters/LauncherPresenter.h
        src/launcher/base/presenters/LauncherPresenter.cpp
        src/launcher/base/views/LauncherView.h
        src/launcher/base/views/LauncherView.cpp
        src/launcher/base/managers/ViewManager.h
        src/launcher/base/managers/ViewManager.cpp
        # DashBoard
        src/launcher/dashboard/views/DashboardView.cpp
        src/launcher/dashboard/views/DashboardView.h
        # Game Settings
        src/launcher/gameSettings/views/GameSettingsView.h
        src/launcher/gameSettings/views/GameSettingsView.cpp
        src/launcher/gameSettings/services/GameSettingsService.h
        src/launcher/gameSettings/models/GameSettingsModel.h
        # Game Updates
        src/launcher/gameUpdates/views/GameUpdatesView.cpp
        src/launcher/gameUpdates/views/GameUpdatesView.h
        src/launcher/gameUpdates/presenters/GameUpdatesPresenter.cpp
        src/launcher/gameUpdates/presenters/GameUpdatesPresenter.h
        src/launcher/gameUpdates/services/GameUpdatesService.h)

# UI files
#file(GLOB_RECURSE UI_FILES *.ui)
set(UI_FILES
        src/launcher/gameSettings/ui/GameSettings.ui
        src/launcher/dashboard/ui/NewsItem.ui
        src/launcher/dashboard/ui/Dashboard.ui
        src/launcher/gameUpdates/ui/GameUpdates.ui)

# Qt resources files
#file(GLOB_RECURSE RCC_FILES *.qrc)
set(RCC_FILES
        resources/icons.qrc
        resources/style.qrc)

include(src/build.cmake)