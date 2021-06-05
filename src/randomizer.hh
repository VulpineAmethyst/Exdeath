#pragma once

#include <random>

#include <QBuffer>
#include <QByteArray>
#include <QFile>
#include <QList>
#include <QString>
#include <QVector>

#include "randodata.hh"

class Randomizer {
public:
    Randomizer(std::mt19937 rand);
    ~Randomizer();

    QBuffer *makeRandom(bool global_innates = false);

private:
    std::mt19937 rng;

    QVector<Skill> *magic1;
    QVector<Skill> *magic2;
    QVector<Skill> *magic3;
    QVector<Skill> *magic4;
    QVector<Skill> *magic5;
    QVector<Skill> *magic6;
    QVector<Skill> *action1;
    QVector<Skill> *action2;
    QVector<Skill> *action3;
    QVector<Skill> *passive1;
    QVector<Skill> *passive2;
    QVector<Skill> *passive3;
    // field passives; to be added to passive1 if they're not going to
    // be assigned globally.
    QVector<Skill> *field;

    QVector<Skill> *tier1;
    QVector<Skill> *tier2;
    QVector<Skill> *tier3;
    QVector<Skill> *tier4;
    QVector<Skill> *tier5;
    QVector<Skill> *tier6;

    // final results
    QVector<Skill> *jobs[JOB_COUNT];
    QVector<int> *costs[JOB_COUNT];
    Skill commands[JOB_COUNT];
    QVector<Skill> *actions;

    QByteArray int2byte(int num);
    void setupData(bool global_innates = false);
    int tierCost(int tier, int minimum);
    void randomizeSkills(void);
    QBuffer *writePatch(void);
};
