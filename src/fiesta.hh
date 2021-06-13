
#pragma once

#include <random>

#include <QBuffer>

#include "randodata.hh"

enum RunType {
    RunNormal = 0,
    Run750,
    RunNo750,
    RunRandom,
    RunRandom750,
    RunRandomNo750,
    RunChaos,
    RunChaos750,
    RunChaosNo750,
    RunPure,
    RunAdvance
};
enum RunModifier {
    ModNone,
    ModFifth,
    ModVoid
};

extern QByteArray be24(int num);

enum Job {
    RNG = 0x00,
    BER = 0x01,
    SAM = 0x02,
    NIN = 0x03,
    DRG = 0x04,
    THF = 0x05,
    MNK = 0x06,
    KNI = 0x07,
    BST = 0x08,
    RED = 0x09,
    BLU = 0x0a,
    SUM = 0x0b,
    TIM = 0x0c,
    BLK = 0x0d,
    WHT = 0x0e,
    MYS = 0x0f,
    FRL = 0x12,
    MIM = 0x13,
    DNC = 0x14,
    BRD = 0x15,
    GEO = 0x16,
    CHM = 0x17,
    GLD = 0x18,
    CAN = 0x19,
    ORC = 0x1a,
    NCR = 0x1b
};

class Fiesta {
public:
    Fiesta(std::mt19937 rand);
    ~Fiesta();
    QBuffer *makeRun(RunType type, RunModifier modifier);

private:
    std::mt19937 rng;
};
