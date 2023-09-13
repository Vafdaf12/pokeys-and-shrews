#pragma once

class ResearchTask;
class ResearchLab;
class Bank;

class Engine {
public:
    Engine(ResearchLab* pLab, Bank* pBank) : m_pLab(pLab), m_pBank(pBank) {}

    /**
     * Event triggered when a request is made to queue a task for research
     * @return Whether the task was successfully queued
     */
    bool researchRequested(ResearchTask* pTask);

    // Event triggered when a research task has completed
    void researchCompleted(ResearchTask* pTask);

    // Event triggered when a research task has been cancelled
    void researchCancelled(ResearchTask* pTask);

private:
    ResearchLab* m_pLab;
    Bank* m_pBank;
};