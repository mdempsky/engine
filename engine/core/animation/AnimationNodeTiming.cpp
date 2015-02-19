// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sky/engine/config.h"
#include "sky/engine/core/animation/AnimationNodeTiming.h"

#include "sky/engine/core/animation/Animation.h"
#include "sky/engine/core/animation/AnimationNode.h"
#include "sky/engine/platform/animation/TimingFunction.h"

namespace blink {

PassRefPtr<AnimationNodeTiming> AnimationNodeTiming::create(AnimationNode* parent)
{
    return adoptRef(new AnimationNodeTiming(parent));
}

AnimationNodeTiming::AnimationNodeTiming(AnimationNode* parent)
    : m_parent(parent)
{
}

double AnimationNodeTiming::delay()
{
    return m_parent->specifiedTiming().startDelay * 1000;
}

double AnimationNodeTiming::endDelay()
{
    return m_parent->specifiedTiming().endDelay * 1000;
}

String AnimationNodeTiming::fill()
{
    Timing::FillMode fillMode = m_parent->specifiedTiming().fillMode;
    switch (fillMode) {
    case Timing::FillModeNone:
        return "none";
    case Timing::FillModeForwards:
        return "forwards";
    case Timing::FillModeBackwards:
        return "backwards";
    case Timing::FillModeBoth:
        return "both";
    case Timing::FillModeAuto:
        return "auto";
    }
    ASSERT_NOT_REACHED();
    return "auto";
}

double AnimationNodeTiming::iterationStart()
{
    return m_parent->specifiedTiming().iterationStart;
}

double AnimationNodeTiming::iterations()
{
    return m_parent->specifiedTiming().iterationCount;
}

String AnimationNodeTiming::getDuration(String propertyName)
{
    if (propertyName != "duration")
        return String();

    if (std::isnan(m_parent->specifiedTiming().iterationDuration))
        return "auto";

    return String::number(m_parent->specifiedTiming().iterationDuration * 1000);
}

double AnimationNodeTiming::playbackRate()
{
    return m_parent->specifiedTiming().playbackRate;
}

String AnimationNodeTiming::direction()
{
    Timing::PlaybackDirection direction = m_parent->specifiedTiming().direction;
    switch (direction) {
    case Timing::PlaybackDirectionNormal:
        return "normal";
    case Timing::PlaybackDirectionReverse:
        return "reverse";
    case Timing::PlaybackDirectionAlternate:
        return "alternate";
    case Timing::PlaybackDirectionAlternateReverse:
        return "alternate-reverse";
    }
    ASSERT_NOT_REACHED();
    return "normal";
}

String AnimationNodeTiming::easing()
{
    return m_parent->specifiedTiming().timingFunction->toString();
}

void AnimationNodeTiming::setDelay(double delay)
{
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setStartDelay(timing, delay);
    m_parent->updateSpecifiedTiming(timing);
}

void AnimationNodeTiming::setEndDelay(double endDelay)
{
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setEndDelay(timing, endDelay);
    m_parent->updateSpecifiedTiming(timing);
}

void AnimationNodeTiming::setFill(String fill)
{
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setFillMode(timing, fill);
    m_parent->updateSpecifiedTiming(timing);
}

void AnimationNodeTiming::setIterationStart(double iterationStart)
{
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setIterationStart(timing, iterationStart);
    m_parent->updateSpecifiedTiming(timing);
}

void AnimationNodeTiming::setIterations(double iterations)
{
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setIterationCount(timing, iterations);
    m_parent->updateSpecifiedTiming(timing);
}

bool AnimationNodeTiming::setDuration(String name, double duration)
{
    if (name != "duration")
        return false;
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setIterationDuration(timing, duration);
    m_parent->updateSpecifiedTiming(timing);
    return true;
}

void AnimationNodeTiming::setPlaybackRate(double playbackRate)
{
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setPlaybackRate(timing, playbackRate);
    m_parent->updateSpecifiedTiming(timing);
}

void AnimationNodeTiming::setDirection(String direction)
{
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setPlaybackDirection(timing, direction);
    m_parent->updateSpecifiedTiming(timing);
}

void AnimationNodeTiming::setEasing(String easing)
{
    Timing timing = m_parent->specifiedTiming();
    TimingInput::setTimingFunction(timing, easing);
    m_parent->updateSpecifiedTiming(timing);
}

} // namespace blink
