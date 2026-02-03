#include "debug_component.h"

using namespace cocos2d;

using namespace debugModule;

bool DebugComponent::init() {
    if (!Component::init()) {
        return false;
    }

    setName(COMPONENT_NAME);

    return true;
}

void DebugComponent::update(float /*dt*/) {
    auto drawNode = getOrCreateDrawNode();
    redrawBorder(drawNode);
}

DrawNode* DebugComponent::getOrCreateDrawNode() {
    auto owner = getOwner();
    if (!owner) {
        return nullptr;
    }

    auto drawNode = dynamic_cast<DrawNode*>(owner->getChildByName(DRAW_NODE_NAME));
    if (!drawNode) {
        drawNode = DrawNode::create();
        drawNode->setName(DRAW_NODE_NAME);

        drawNode->setLocalZOrder(INT_MAX);

        owner->addChild(drawNode);
    }

    return drawNode;
}

void DebugComponent::redrawBorder(DrawNode* drawNode) {
    if (!drawNode) {
        return;
    }

    drawNode->clear();

    const cocos2d::Size size = getOwner()->getContentSize();
    if (size.width <= 0 || size.height <= 0) {
        return;
    }

    Vec2 rect[4] = {
        Vec2(0, 0),
        Vec2(size.width, 0),
        Vec2(size.width, size.height),
        Vec2(0, size.height)
    };

    drawNode->drawPoly(rect, 4, true, _debugColor);
}

//
// -------- static helpers --------
//

void DebugComponent::createDebugComponent(Node* node) {
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([node]() {
        if (!node || isDebugComponent(node)) {
            return;
        }
        auto component = DebugComponent::create();
        node->addComponent(component);
        node->scheduleUpdate();
    });
}

bool DebugComponent::isDebugComponent(Node* node) {
    if (!node) {
        return false;
    }

    return node->getComponent(COMPONENT_NAME) != nullptr;
}

void DebugComponent::removeDebugComponent(Node* node) {
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([node]() {
        if (!node) {
            return;
        }
        if (auto comp = node->getComponent(COMPONENT_NAME)) {
            node->removeComponent(comp);
        }

        if (auto drawNode = node->getChildByName(DRAW_NODE_NAME)) {
            drawNode->removeFromParent();
        }
    });
}

void DebugComponent::setDebugColor(Node* node, const Color4F& color) {
    if (auto comp = dynamic_cast<DebugComponent*>(node->getComponent(COMPONENT_NAME))) {
        comp->_debugColor = color;
    }
}

const Color4F& DebugComponent::getDebugColor(Node* node) {
    if (auto comp = dynamic_cast<DebugComponent*>(node->getComponent(COMPONENT_NAME))) {
        return comp->_debugColor;
    }
    return Color4F::WHITE;
}
