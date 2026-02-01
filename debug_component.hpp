#pragma once
#ifndef DEBUG_COMPONENT_HPP
#define DEBUG_COMPONENT_HPP

#include "cocos2d.h"

namespace debugModule {

class DebugComponent final : public cocos2d::Component {
public:
  static constexpr const char* COMPONENT_NAME = "DebugComponent";
  static constexpr const char* DRAW_NODE_NAME = "DebugDrawNode";

  // --- component lifecycle ---
  virtual bool init() override;
  virtual void update(float dt) override;

  CREATE_FUNC(DebugComponent);

  // --- static helpers ---
  static void createDebugComponent(cocos2d::Node* node);
  static bool isDebugComponent(cocos2d::Node* node);
  static void removeDebugComponent(cocos2d::Node* node);

  static void setDebugColor(cocos2d::Node* node, const cocos2d::Color4F& color);
  static const cocos2d::Color4F& getDebugColor(cocos2d::Node* node);

private:
  cocos2d::DrawNode* getOrCreateDrawNode();
  void redrawBorder(cocos2d::DrawNode* drawNode);

protected:
  static cocos2d::Color4F _debugColor;
};

} // namespace debugModule

#endif // DEBUG_COMPONENT_HPP
