#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {}

    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow) { 
        // offsetPixels = pWindow - (mWindowSize / 2)
        // offsetWorld = offsetPixels * mWorldUnitsPerPixel
        // pWorld = mViewCenterWorld + offsetWorld
        return {mViewCenterWorld + (pWindow - mWindowSize / 2.0f) * mWorldUnitsPerPixel};
    };

    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld) { 
        // offsetWorld = pWorld - mViewCenterWorld
        // offsetPixels = offsetWorld / mWorldUnitsPerPixel
        // pWindow = offsetPixels + mWindowSize / 2
        return {(pWorld - mViewCenterWorld) / mWorldUnitsPerPixel + mWindowSize / 2.0f}; 
    };

    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent) {
        return windowToWorld(pWindowPercent * mWindowSize);
    };

    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld) { 
        return worldToWindow(pWorld) / mWindowSize;
    };

    void translateWorld(const sf::Vector2f& deltaWorld) {
        mViewCenterWorld += deltaWorld;
    };

    void translateWindow(const sf::Vector2f& deltaScreen) {
        translateWorld(deltaScreen * mWorldUnitsPerPixel);
    };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) {
        translateWindow(deltaScreenPercent * mWindowSize);
    };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) {
        translateWorld(pWorld - windowToWorld(pWindow));
    };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) {
        setCamera(pWorld, pWindowPercent * mWindowSize);
    };

    void setCameraCenter(const sf::Vector2f& pWorld) {
        mViewCenterWorld = pWorld;
    };

    sf::Vector2f getCameraCenter() const { 
        return {mViewCenterWorld}; 
    };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
