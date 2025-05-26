// this mod was planned before i even knew what happy textures was
// introducing happy textures, css edition

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/cocos/extensions/GUI/CCControlExtension/CCScale9Sprite.h>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <climits>

using namespace geode::prelude;

struct Styles {
    std::string rootClass;
    std::vector<std::pair<std::string, std::string>> path;

    float x      = NAN;
    float y      = NAN;
    float scale  = NAN;
    float scaleX = NAN;
    float scaleY = NAN;
    float rotation = NAN;
    float skewX = NAN;
    float skewY = NAN;
    float anchorX = NAN;
    float anchorY = NAN;
    int zOrder = INT_MIN;

    bool visible = true;
    bool hasVisible = false;

    bool ignoreAnchorForPosition = false;
    bool hasIgnoreAnchor = false;

    float contentWidth = NAN;
    float contentHeight = NAN;

    bool hasColor = false;
    ccColor3B color = { 255, 255, 255 };

    float opacity = NAN;
};

static std::vector<Styles> g_rules;

static std::string trim(const std::string& s) {
    auto a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    auto b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static void loadStyles() {
    g_rules.clear();

    std::string path;
    try {
        path = Mod::get()->getSettingValue<std::filesystem::path>("stylesheet").string();
    } catch (...) {
        path = "";
    }

    std::ifstream file(path);

    if (path.empty() || !std::filesystem::exists(path)) {
        log::warn("Stylesheet file '{}' does not exist or is empty.", path);
        return;
    }

    if (!file.is_open()) {
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    std::regex blockRx(R"(([^{}]+)\{([^{}]+)\})");
    std::smatch blockMatch;
    auto it = content.cbegin();
    while (std::regex_search(it, content.cend(), blockMatch, blockRx)) {
        std::string selectorLine = trim(blockMatch[1].str());
        std::string body         = blockMatch[2].str();
        it = blockMatch.suffix().first;

        std::istringstream ss(selectorLine);
        std::vector<std::string> tokens;
        for (std::string tok; ss >> tok; )
            tokens.push_back(tok);
        if (tokens.empty()) continue;

        Styles rule;
        rule.rootClass = tokens[0];

        for (size_t i = 1; i < tokens.size(); ++i) {
            auto part = tokens[i];
            auto pos  = part.find(':');
            if (pos == std::string::npos) continue;
            auto cls = part.substr(0, pos);
            auto id  = part.substr(pos + 1);
            rule.path.emplace_back(cls, id);
        }

        std::regex propRx(R"(\b(x|y|scale|scale-x|scale-y|rotation|skew-x|skew-y|anchor-x|anchor-y|z-order|visible|color|opacity|content-width|content-height)\s*:\s*([^;]+)\s*;)");
        std::smatch propMatch;
        auto it2 = body.cbegin();
        while (std::regex_search(it2, body.cend(), propMatch, propRx)) {
            std::string key = propMatch[1].str();
            std::string val = trim(propMatch[2].str());

            try {
                if (key == "x") {
                    rule.x = std::stof(val);
                }
                else if (key == "y") {
                    rule.y = std::stof(val);
                }
                else if (key == "scale") {
                    rule.scale = std::stof(val);
                }
                else if (key == "scale-x") {
                    rule.scaleX = std::stof(val);
                }
                else if (key == "scale-y") {
                    rule.scaleY = std::stof(val);
                }
                else if (key == "rotation") {
                    rule.rotation = std::stof(val);
                }
                else if (key == "skew-x") {
                    rule.skewX = std::stof(val);
                }
                else if (key == "skew-y") {
                    rule.skewY = std::stof(val);
                }
                else if (key == "anchor-x") {
                    rule.anchorX = std::stof(val);
                }
                else if (key == "anchor-y") {
                    rule.anchorY = std::stof(val);
                }
                else if (key == "z-order") {
                    rule.zOrder = std::stoi(val);
                }
                else if (key == "visible") {
                    rule.visible = (val == "true");
                    rule.hasVisible = true;
                }
                else if (key == "content-width") {
                    rule.contentWidth = std::stof(val);
                }
                else if (key == "content-height") {
                    rule.contentHeight = std::stof(val);
                }
                else if (key == "color") {
                    std::regex colorRx(R"((\d+)\s*,\s*(\d+)\s*,\s*(\d+))");
                    std::smatch colorMatch;
                    if (std::regex_match(val, colorMatch, colorRx)) {
                        rule.color.r = static_cast<GLubyte>(std::stoi(colorMatch[1].str()));
                        rule.color.g = static_cast<GLubyte>(std::stoi(colorMatch[2].str()));
                        rule.color.b = static_cast<GLubyte>(std::stoi(colorMatch[3].str()));
                        rule.hasColor = true;
                    }
                }
                else if (key == "opacity") {
                    rule.opacity = std::stof(val);
                }
            }
            catch (...) {
                log::warn("Failed to set property '{}: {}'", key, val);
            }

            it2 = propMatch.suffix().first;
        }

        bool hasAny =
            !std::isnan(rule.x)       || !std::isnan(rule.y)       ||
            !std::isnan(rule.scale)   || !std::isnan(rule.scaleX)   ||
            !std::isnan(rule.scaleY)  || !std::isnan(rule.rotation) ||
            !std::isnan(rule.skewX)   || !std::isnan(rule.skewY)    ||
            !std::isnan(rule.anchorX) || !std::isnan(rule.anchorY)  ||
            rule.zOrder != INT_MIN    ||
            rule.hasVisible           ||
            rule.hasIgnoreAnchor      ||
            !std::isnan(rule.contentWidth) || !std::isnan(rule.contentHeight) ||
            rule.hasColor             || !std::isnan(rule.opacity);

        if (hasAny) {
            g_rules.push_back(std::move(rule));
        }
    }
}

static CCNode* findType(CCNode* start, const std::vector<std::pair<std::string, std::string>>& path) {
    CCNode* current = start;
    for (auto& [cls, id] : path) {
        auto node = current->getChildByIDRecursive(id);
        if (!node) return nullptr;

        if (cls == "CCMenu") {
            auto casted = typeinfo_cast<CCMenu*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCMenuItemSpriteExtra") {
            auto casted = typeinfo_cast<CCMenuItemSpriteExtra*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCSprite") {
            auto casted = typeinfo_cast<CCSprite*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCSpriteExtra") {
            auto casted = typeinfo_cast<CCSpriteExtra*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCSpriteBatchNode") {
            auto casted = typeinfo_cast<CCSpriteBatchNode*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCLabelBMFont") {
            auto casted = typeinfo_cast<CCLabelBMFont*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCCounterLabel") {
            auto casted = typeinfo_cast<CCCounterLabel*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "BoomScrollLayer") {
            auto casted = typeinfo_cast<BoomScrollLayer*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCTextInputNode") {
            auto casted = typeinfo_cast<CCTextInputNode*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCScale9Sprite") {
            auto casted = typeinfo_cast<CCScale9Sprite*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "GJGroundLayer") {
            auto casted = typeinfo_cast<GJGroundLayer*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCNode") {
            auto casted = typeinfo_cast<CCNode*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "GJEffectManager") {
            auto casted = typeinfo_cast<GJEffectManager*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "GJUINode") {
            auto casted = typeinfo_cast<GJUINode*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "Slider") {
            auto casted = typeinfo_cast<Slider*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCParticleSystemQuad") {
            auto casted = typeinfo_cast<CCParticleSystemQuad*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CCParticleSystemQuad") {
            auto casted = typeinfo_cast<CCParticleSystemQuad*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "EditorUI") {
            auto casted = typeinfo_cast<EditorUI*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "UILayer") {
            auto casted = typeinfo_cast<UILayer*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "EditButtonBar") {
            auto casted = typeinfo_cast<EditButtonBar*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else if (cls == "CustomSongWidget") {
            auto casted = typeinfo_cast<CustomSongWidget*>(node);
            if (!casted) return nullptr;
            current = casted;
        }
        else {
            current = node;
        }
    }
    return current;
}


static void applyStyles(CCNode* layerRoot, const std::string& layerName) {
    loadStyles();
    for (auto& rule : g_rules) {
        if (rule.rootClass != layerName) continue;

        CCNode* target = findType(layerRoot, rule.path);
        if (!target) {
            std::string desc = layerName;
            for (auto& [cls, id] : rule.path) {
                desc += " " + cls + ":" + id;
            }
            continue;
        }

        auto oldPos = target->getPosition();
        float newX = std::isnan(rule.x) ? oldPos.x : rule.x;
        float newY = std::isnan(rule.y) ? oldPos.y : rule.y;
        target->setPosition({ newX, newY });

        if (!std::isnan(rule.scale)) {
            target->setScale(rule.scale);
        }
        if (!std::isnan(rule.scaleX)) {
            target->setScaleX(rule.scaleX);
        }
        if (!std::isnan(rule.scaleY)) {
            target->setScaleY(rule.scaleY);
        }

        if (!std::isnan(rule.rotation)) {
            target->setRotation(rule.rotation);
        }

        if (!std::isnan(rule.skewX)) {
            target->setSkewX(rule.skewX);
        }

        if (!std::isnan(rule.skewY)) {
            target->setSkewY(rule.skewY);
        }

        if (!std::isnan(rule.anchorX) && !std::isnan(rule.anchorY)) {
            target->setAnchorPoint({ rule.anchorX, rule.anchorY });
        }

        if (rule.zOrder != INT_MIN) {
            target->setZOrder(rule.zOrder);
        }

        if (rule.hasVisible) {
            target->setVisible(rule.visible);
        }

        if (rule.hasColor || !std::isnan(rule.opacity)) {
            auto rgbaNode = dynamic_cast<CCRGBAProtocol*>(target);
            if (rgbaNode) {
                if (rule.hasColor) {
                    rgbaNode->setColor(rule.color);
                }
                if (!std::isnan(rule.opacity)) {
                    float clamped = std::clamp(rule.opacity, 0.f, 255.f);
                    rgbaNode->setOpacity(static_cast<GLubyte>(clamped));
                }
            }
            else {
                std::string styledID = rule.path.empty() ? layerName : rule.path.back().second;
            }
        }

        if (rule.hasIgnoreAnchor) {
            target->ignoreAnchorPointForPosition(rule.ignoreAnchorForPosition);
        }

        if (!std::isnan(rule.contentWidth) && !std::isnan(rule.contentHeight)) {
            target->setContentSize({ rule.contentWidth, rule.contentHeight });
        }

        std::string styledID = rule.path.empty() ? layerName : rule.path.back().second;

        /*
        log::info(
            "GStyle: '{}' in {} → pos=({}, {}), scale={}{}{}, rot={}°, skew=({}, {}), anchor=({}, {}), z={}, vis={}, color=({}, {}, {}), opa={}, ignoreAnchor={}, contentSize=({}, {})",
            styledID,
            layerName,
            newX, newY,
            std::isnan(rule.scale)   ? -1.f : rule.scale,
            std::isnan(rule.scaleX)  ?  0.f : rule.scaleX,
            std::isnan(rule.scaleY)  ?  0.f : rule.scaleY,
            std::isnan(rule.rotation)?  0.f : rule.rotation,
            std::isnan(rule.skewX)   ?  0.f : rule.skewX,
            std::isnan(rule.skewY)   ?  0.f : rule.skewY,
            std::isnan(rule.anchorX) ?  0.f : rule.anchorX,
            std::isnan(rule.anchorY) ?  0.f : rule.anchorY,
            rule.zOrder == INT_MIN   ?  0   : rule.zOrder,
            rule.hasVisible          ? (rule.visible ? "true" : "false") : "n/a",
            rule.hasColor            ? rule.color.r : 255,
            rule.hasColor            ? rule.color.g : 255,
            rule.hasColor            ? rule.color.b : 255,
            std::isnan(rule.opacity) ? 255.f : rule.opacity,
            rule.hasIgnoreAnchor     ? (rule.ignoreAnchorForPosition ? "true" : "false") : "n/a",
            std::isnan(rule.contentWidth)  ? 0.f : rule.contentWidth,
            std::isnan(rule.contentHeight) ? 0.f : rule.contentHeight
        );
        */
    }
}

#include "layers.hpp"