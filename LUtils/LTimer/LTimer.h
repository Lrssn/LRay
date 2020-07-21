#pragma once
#include "../pch.h"

namespace LUtils {
    class LTimer {
    public:
        void start() {
            m_StartTime = std::chrono::high_resolution_clock::now();
            m_bRunning = true;
        }

        void stop() {
            m_EndTime = std::chrono::high_resolution_clock::now();
            m_bRunning = false;
        }

        double elapsedHours() {
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

            if (m_bRunning) {
                endTime = std::chrono::high_resolution_clock::now();
            } else {
                endTime = m_EndTime;
            }

            return std::chrono::duration_cast<std::chrono::hours>(endTime - m_StartTime).count();
        }

        double elapsedMinutes() {
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

            if (m_bRunning) {
                endTime = std::chrono::high_resolution_clock::now();
            } else {
                endTime = m_EndTime;
            }

            return std::chrono::duration_cast<std::chrono::minutes>(endTime - m_StartTime).count();
        }

        double elapsedSeconds() {
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

            if (m_bRunning) {
                endTime = std::chrono::high_resolution_clock::now();
            } else {
                endTime = m_EndTime;
            }

            return std::chrono::duration_cast<std::chrono::seconds>(endTime - m_StartTime).count();

        }

        double elapsedMilliseconds() {
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

            if (m_bRunning) {
                endTime = std::chrono::high_resolution_clock::now();
            } else {
                endTime = m_EndTime;
            }

            return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
        }

        double elapsedMicroseconds() {
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

            if (m_bRunning) {
                endTime = std::chrono::high_resolution_clock::now();
            } else {
                endTime = m_EndTime;
            }

            return std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_StartTime).count();
        }

        double elapsedNanoseconds() {
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

            if (m_bRunning) {
                endTime = std::chrono::high_resolution_clock::now();
            } else {
                endTime = m_EndTime;
            }

            return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_StartTime).count();
        }
        

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTime;
        bool m_bRunning = false;
    };
}


