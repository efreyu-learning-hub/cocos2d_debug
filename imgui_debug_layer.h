#ifndef IMGUI_DEBUG_LAYER_H
#define IMGUI_DEBUG_LAYER_H

#ifdef IMGUI_ENABLED

#include "cocos2d.h"

#if defined(CC_BUILD_WITH_DRANGBONES) && CC_BUILD_WITH_DRANGBONES
#include "DragonBones/CCDragonBonesHeaders.h"
#endif

#ifdef COCOS2D_VERSION
#include "CCImGuiLayer.h"
#include <CCIMGUI.h>
#include <imgui.h>
#include <imgui_internal.h>
#else
#include "ImGuiEXT/CCImGuiEXT.h"
#include "ImGuiEXT/imgui/imgui.h"
#include "ImGuiEXT/imgui/imgui_internal.h"
#endif
#include "cocos2d.h"
#include "platform/CCPlatformConfig.h"
#include "ui/CocosGUI.h"
#include <algorithm>
#include <functional>
#include <list>
#include <string>
#include <tuple>
#include <vector>

namespace debugModule {

    class ImGuiDebugLayer : public cocos2d::Layer {
    protected:
        void update(float dt) override {
            if (!this->isVisible()) {
                this->setVisible(true);
            }
        }

    public:
        static void initializeLayer();
        static std::string demangle(const char* name);
        ImGuiDebugLayer() {}
        ~ImGuiDebugLayer() {
            resetDebugModules();
        }
        CREATE_FUNC(ImGuiDebugLayer);
        bool init() override;
        void resetDebugModules();
        void addDebugModules(const std::pair<std::string, std::function<void()>>&);
        void drawImgui();

        static bool
          Combo(const char* label, int* current_item, const std::vector<std::string>& items, int items_count, int height_in_items = -1);

    private:
        void initEvents();
        /// Debug data
        void debugToggleRow(Node*);
        /// Node editor
        void showNodeEditor(bool* editorOpened);
        ImRect renderTree(cocos2d::Vector<Node*> n);
        ImRect renderPreferences(Node*);

        cocos2d::EventListenerKeyboard* keyboardListener = nullptr;

        bool m_enabled = true;
        float default_width = 0.0f;
        /***
         * Debug buttonNode properties
         */
        int debugBtnW = 65;
        int debugBtnH = 80;

        /***
         * Node editor window
         */
        int nodeEditorW = 430;
        int nodeEditorH = 450;
        Node* lastTarget = nullptr;
        std::vector<std::pair<std::string, std::function<void()>>> debugModules;
    };
}// namespace debugModule

#else
namespace debugModule {
    class ImGuiDebugLayer : public cocos2d::Layer {
    public:
        static void initializeLayer();
    };
}
#endif // IMGUI_ENABLED
#endif // IMGUI_DEBUG_LAYER_H
