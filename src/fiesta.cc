/*
 * Copyright (c) 2023, Síle Ekaterin Liszka.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the software nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fiesta.hh"

Fiesta::Fiesta(std::mt19937 rand) {
    rng = rand;
}

Fiesta::~Fiesta() {}

const int wind_addr[7] = {
    0x3d6060,
    0x3d6062,
    0x3d6064,
    0x3d6066,
    0x3d6068,
    0x3d606a,
    0x4aa87,
};
const int job_addr[2] = {
    0x4AFC2,
    0x4AA46,
};
const int water_addr[6] = {
    0x3d152e,
    0x3d153a,
    0x3d1546,
    0x3d1552,
    0x3d155e,
    0x3ce4c4,
};
const int fire_addr[5] = {
    0x3d8285,
    0x3d8287,
    0x3d8289,
    0x3d0c62,
    0x3d0c64,
};
const int earth_addr[4] = {
    0x3cb039,
    0x3cb03b,
    0x3cb03d,
    0x3cb03f,
};
const int adv_addr[3] = {
    0x3e2a45,
    0x3e2a62,
    0x3e2a7d,
};

QMap<int,int> id2menu = {
    {KNI, 0x00},
    {MNK, 0x01},
    {THF, 0x02},
    {DRG, 0x03},
    {NIN, 0x04},
    {SAM, 0x05},
    {BER, 0x06},
    {RNG, 0x07},
    {MYS, 0x08},
    {WHT, 0x09},
    {BLK, 0x0a},
    {TIM, 0x0b},
    {SUM, 0x0c},
    {BLU, 0x0d},
    {RED, 0x0e},
    {BST, 0x0f},
    {CHM, 0x10},
    {GEO, 0x11},
    {BRD, 0x12},
    {DNC, 0x13},
    {MIM, 0x14},
    {FRL, 0x15},
    // bold assumptions, Cotton
    {GLD, 0x16},
    {CAN, 0x17},
    {ORC, 0x18},
    {NCR, 0x19},
};

QBuffer *Fiesta::makeRun(RunType type, RunModifier modifier) {
    QBuffer *patch = new QBuffer();
    QVector<char> wind, water, fire, earth;
    char jobI, jobA, jobF, jobE, jobK;

    switch (type) {
        default:
        case RunNormal:
            wind  = {THF, MNK, KNI, BLU, BLK, WHT};
            water = {BER, RED, TIM, SUM, MYS};
            fire  = {RNG, NIN, BST, GEO, BRD};
            earth = {SAM, DRG, DNC, CHM};
            break;
        case Run750:
            wind  = {BLU, BLK, WHT};
            water = {RED, TIM, SUM};
            fire  = {GEO, BRD};
            earth = {DNC, CHM};
            break;
        case RunNo750:
            wind  = {THF, MNK, KNI};
            water = {BER, MYS};
            fire  = {RNG, NIN, BST};
            earth = {SAM, DRG};
            break;
        case RunRandom:
            wind  = {THF, MNK, KNI, BLU, BLK, WHT};
            water = {THF, MNK, KNI, BLU, BLK, WHT, BER, RED, TIM, SUM, MYS};
            fire  = {THF, MNK, KNI, BLU, BLK, WHT, BER, RED, TIM, SUM, MYS, RNG, NIN, BST, GEO, BRD};
            earth = {THF, MNK, KNI, BLU, BLK, WHT, BER, RED, TIM, SUM, MYS, RNG, NIN, BST, GEO, BRD, SAM, DRG, DNC, CHM};
            break;
        case RunRandom750:
            wind  = {BLU, BLK, WHT};
            water = {BLU, BLK, WHT, RED, TIM, SUM};
            fire  = {BLU, BLK, WHT, RED, TIM, SUM, GEO, BRD};
            earth = {BLU, BLK, WHT, RED, TIM, SUM, GEO, BRD, DNC, CHM};
            break;
        case RunRandomNo750:
            wind  = {THF, MNK, KNI};
            water = {THF, MNK, KNI, BER, MYS};
            fire  = {THF, MNK, KNI, BER, MYS, RNG, NIN, BST};
            earth = {THF, MNK, KNI, BER, MYS, RNG, NIN, BST, SAM, DRG};
            break;
        case RunChaos:
            wind  = {THF, MNK, KNI, BLU, BLK, WHT, BER, RED, TIM, SUM, MYS, RNG, NIN, BST, GEO, BRD, SAM, DRG, DNC, CHM};
            water = wind;
            fire  = water;
            earth = fire;
            break;
        case RunChaos750:
            wind  = {BLU, BLK, WHT, RED, TIM, SUM, GEO, BRD, DNC, CHM};
            water = wind;
            fire  = water;
            earth = fire;
            break;
        case RunChaosNo750:
            wind  = {THF, MNK, KNI, BER, MYS, RNG, NIN, BST, SAM, DRG};
            water = wind;
            fire  = water;
            earth = fire;
            break;
        case RunPure:
            wind = {THF, MNK, KNI, BLU, BLK, WHT, BER, RED, TIM, SUM, MYS, RNG, NIN, BST, GEO, BRD, SAM, DRG, DNC, CHM, MIM, FRL};
            break;
        case RunAdvance:
            wind  = {THF, MNK, KNI, BLU, BLK, WHT, TIM};
            water = {BER, RED, SUM, MYS, NIN, BST, GEO};
            fire  = {RNG, BRD, SAM, DRG, DNC, CHM};
            earth = {GLD, CAN, ORC};
            break;
    }

    // pick Jobs
    std::shuffle(wind.begin(), wind.end(), rng);
    if (type != RunPure) {
        std::shuffle(water.begin(), water.end(), rng);
        std::shuffle(fire.begin(), fire.end(), rng);
        std::shuffle(earth.begin(), earth.end(), rng);

        jobI = wind.first();
        jobA = water.first();
        jobF = fire.first();
        jobE = earth.first();
        if (modifier == ModVoid) {
            // nix a job
        } else if (modifier == ModFifth) {
            earth.removeFirst();
            jobK = earth.first();
        }
    } else {
        jobI = wind.first();
        wind.removeFirst();
        jobA = wind.first();
        wind.removeFirst();
        jobF = wind.first();
        wind.removeFirst();
        jobE = wind.first();
        if (modifier == ModVoid) {
            // nix a job
        } else {
            wind.removeFirst();
            jobK = wind.first();
        }
    }

    // write patch
    patch->open(QIODevice::ReadWrite);
    patch->write("PATCH", 5);

    // nix gaining FRL outside of actually rolling it
    patch->write(be24(0x3d4f6d));
    patch->write("\x00\x02", 2);
    patch->write("\x32\xfe", 2);
    patch->write(be24(0x55202));
    patch->write("\x00\x02", 2);
    patch->write("\x00\x00", 2);

    // job menu adjustments
    for (int i = 0; i < 2; i++) {
        char temp[2] = {static_cast<char>(id2menu[jobI] & 0xFF), '\0'};
        patch->write(be24(job_addr[i]));
        patch->write("\x00\x01", 2);
        patch->write(temp, 1);
    }

    // job assignments
    for (int i = 0; i < 7; i++) {
        char temp[2] = {jobI, '\0'};
        patch->write(be24(wind_addr[i] + 1));
        patch->write("\x00\x01", 2);
        patch->write(temp, 1);
    }
    for (int i = 0; i < 6; i++) {
        char temp[2] = {jobA, '\0'};
        patch->write(be24(water_addr[i] + 1));
        patch->write("\x00\x01", 2);
        patch->write(temp, 1);
    }
    for (int i = 0; i < 5; i++) {
        char temp[2] = {jobF, '\0'};
        patch->write(be24(fire_addr[i] + 1));
        patch->write("\x00\x01", 2);
        patch->write(temp, 1);
    }
    for (int i = 0; i < 4; i++) {
        char temp[2] = {jobE, '\0'};
        patch->write(be24(earth_addr[i] + 1));
        patch->write("\x00\x01", 2);
        patch->write(temp, 1);
    }
    for (int i = 0; i < 3; i++) {
        char temp[2];
        if (modifier == ModFifth) {
            temp[0] = jobK;
        } else {
            temp[0] = jobE;
        }
        temp[1] = '\0';
        patch->write(be24(adv_addr[i] + 1));
        patch->write("\x00\x01", 2);
        patch->write(temp,1);
    }
    patch->write("EOF", 3);
    patch->seek(0);

    return patch;
}

//   KNI MNK THF DRG NIN SAM
// BER RNG MYS WHT BLK TIM SUM
//   BLU RED BST CHM GEO BRD
// DNC NCR ORC CAN GLD MIM FRL

//  07 06 05 04 03 02
// 01 00 0F 0E 0D 0C 0B
//  0A 09 08 1A 1B 19
// 18 BLK SUM TIM BLU 17 16
//  MYS WHT 01 02