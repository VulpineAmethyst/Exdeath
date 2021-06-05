/*
 * Copyright (c) 2021, Sheila Aman.
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

#include <algorithm>

#include "randomizer.hh"

Randomizer::Randomizer(std::mt19937 rand) {
    rng = rand;
}
Randomizer::~Randomizer() {}

QByteArray Randomizer::int2byte(int num) {
    QByteArray temp;
    temp.append(num & 0xFF);
    temp.append((num >> 8) & 0xFF);
    temp.append((num >> 16) & 0xFF);
    temp.append((num >> 24) & 0xFF);
    return temp;
}

static std::uniform_int_distribution<> dist_13(1, 3);
static std::uniform_int_distribution<> dist_14(1, 4);
static std::uniform_int_distribution<> dist_15(1, 5);
static std::uniform_int_distribution<> dist_16(1, 6);
static std::uniform_int_distribution<> dist_17(1, 7);
static std::uniform_int_distribution<> dist_1x(1, 10);

int Randomizer::tierCost(int tier, int minimum) {
    int guess;
    switch (tier) {
        case 0:
            guess = (1 + dist_15(rng)) * 5;
            if ((guess <= (minimum + 10)) && (minimum != 0)) {
                return minimum + (1 + dist_13(rng)) * 5;
            }
            return guess;
            break;
        case 1:
            guess = (8 + dist_17(rng)) * 5;
            if ((guess <= (minimum + 15)) && (minimum != 0)) {
                return minimum + (2 + dist_13(rng)) * 5;
            }
            return guess;
            break;
        case 2:
            guess = (15 + dist_15(rng)) * 5;
            if ((guess <= (minimum + 25)) && (minimum != 0)) {
                return minimum + (4 + dist_16(rng)) * 5;
            }
            return guess;
            break;
        case 3:
            guess = (14 + dist_15(rng)) * 10;
            if ((guess <= (minimum + 40)) && (minimum != 0)) {
                return minimum + (3 + dist_13(rng)) * 10;
            }
            return guess;
            break;
        case 4:
            guess = (24 + dist_16(rng)) * 10;
            if ((guess <= (minimum + 50)) && (minimum != 0)) {
                return minimum + (4 + dist_16(rng)) * 10;
            }
            return guess;
            break;
        case 5:
            guess = (14 + dist_16(rng)) + (19 + dist_16(rng));
            guess *= 10;
            if (guess <= (minimum + 100)) {
                return minimum + (10 + dist_1x(rng)) * 10;
            }
            return guess;
            break;
        default:
            return minimum;
    }
}

void Randomizer::setupData(bool global_innates) {
    magic1 = new QVector<Skill>({
        Spellblade1,
        White1,
        Black1,
        Time1,
        Red1,
        Summon1
    });

    magic2 = new QVector<Skill>({
        Spellblade2,
        White2,
        Black2,
        Time2,
        Red2,
        Summon2
    });

    magic3 = new QVector<Skill>({
        Spellblade3,
        White3,
        Black3,
        Time3,
        Red3,
        Summon3
    });

    magic4 = new QVector<Skill>({
        Spellblade4,
        White4,
        Black4,
        Time4
    });

    magic5 = new QVector<Skill>({
        Spellblade5,
        White5,
        Black5,
        Time5,
        Summon4
    });

    magic6 = new QVector<Skill>({
        Spellblade6,
        White6,
        Black6,
        Time6,
        Summon5
    });

    action1 = new QVector<Skill>({
        Guard,
        Kick,
        Chakra,
        Lancet,
        Image,
        Mineuchi,
        Aim,
        Check,
        Calm,
        Recover,
        Hide,
        Flirt,
        Scan
    });
    action2 = new QVector<Skill>({
        Steal,
        Jump,
        Focus,
        Smoke,
        Flee,
        Gaia,
        Dance,
        Blue,
        Revive,
        Animals,
        Catch,
        Sing,
        Call
    });
    action3 = new QVector<Skill>({
        Throw,
        GilToss,
        Iainuki,
        RapidFire,
        Control,
        Mix,
        Drink,
        DualCast
    });
    passive1 = new QVector<Skill>({
        HP10,
        MP10,
        Pharmacology,
        Cover,
        Counter,
        Learning,
        MagicShield,
        Berserk,
        FindPassages,
        LightStep,
        FindPits,
        Sprint
    });
    passive2 = new QVector<Skill>({
        EquipSpear,
        EquipArmor,
        EquipBow,
        EquipKatana,
        MP30,
        HP20,
        Barehanded,
        Shirahadori,
        Vigilance,
        FirstStrike
    });
    passive3 = new QVector<Skill>({
        EquipRods,
        TwoHanded,
        HP30,
        EquipAxe,
        EquipRibbon,
        EquipSword,
        ArtfulDodger,
        EquipHarp,
        EquipWhip,
        EquipShield
    });
    field = new QVector<Skill>({
        HP10,
        MP10,
        Pharmacology,
        Cover,
        Counter,
        MagicShield,
        Berserk
    });
    if (!global_innates) {
        passive1->append(*field);
    }

    tier1 = new QVector<Skill>(*magic1 + *passive1);
    tier2 = new QVector<Skill>(*magic2 + *action1);
    tier3 = new QVector<Skill>(*magic3 + *passive2);
    tier4 = new QVector<Skill>(*magic4 + *action2);
    tier5 = new QVector<Skill>(*magic5 + *passive3);
    tier6 = new QVector<Skill>(*magic6 + *action3);
}

void Randomizer::randomizeSkills(void) {
    QVector<Skill> *l_tier1 = new QVector<Skill>(*tier1);
    QVector<Skill> *l_tier2 = new QVector<Skill>(*tier2);
    QVector<Skill> *l_tier3 = new QVector<Skill>(*tier3);
    QVector<Skill> *l_tier4 = new QVector<Skill>(*tier4);
    QVector<Skill> *l_tier5 = new QVector<Skill>(*tier5);
    QVector<Skill> *l_tier6 = new QVector<Skill>(*tier6);
    actions = new QVector<Skill>();
    QVector<Skill> *skills[6];
    int tierpos = 0;

    std::shuffle(l_tier1->begin(), l_tier1->end(), rng);
    std::shuffle(l_tier2->begin(), l_tier2->end(), rng);
    std::shuffle(l_tier3->begin(), l_tier3->end(), rng);
    std::shuffle(l_tier4->begin(), l_tier4->end(), rng);
    std::shuffle(l_tier5->begin(), l_tier5->end(), rng);
    std::shuffle(l_tier6->begin(), l_tier6->end(), rng);

    skills[0] = new QVector<Skill>(*l_tier1);
    skills[1] = new QVector<Skill>(*l_tier2);
    skills[2] = new QVector<Skill>(*l_tier3);
    skills[3] = new QVector<Skill>(*l_tier4);
    skills[4] = new QVector<Skill>(*l_tier5);
    skills[5] = new QVector<Skill>(*l_tier6);
    QVector<Skill> *act1 = new QVector<Skill>(*magic6 + *action3);
    QVector<Skill> *act2 = new QVector<Skill>(*magic4 + *action2);
    QVector<Skill> *act3 = new QVector<Skill>(*magic2 + *action1);
    std::shuffle(act1->begin(), act1->end(), rng);
    std::shuffle(act2->begin(), act2->end(), rng);
    std::shuffle(act3->begin(), act3->end(), rng);
    actions->append(*act1);
    actions->append(*act2);
    actions->append(*act3);

    for (int i = 0; i < 20; i++) {
        jobs[i] = new QVector<Skill>();
        costs[i] = new QVector<int>();
    }
    QVector<int> *job_list = new QVector<int>();
    for (int i = 0; i < JOB_COUNT; i++) {
        job_list->append(i);
    }
    std::shuffle(job_list->begin(), job_list->end(), rng);

    while (tierpos < 5) {
        for (int i = 0; i < JOB_COUNT; i++) {
            int job = job_list->at(i);
            if (skills[tierpos]->count() < 1) {
                tierpos += 1;
            }
            if (skills[tierpos]->isEmpty()) {
                break;
            }
            Skill temp = skills[tierpos]->first();
            int minimum = 0;
            if (costs[job]->count() > 0) {
                minimum = costs[i]->last();
            }
            skills[tierpos]->removeFirst();
            jobs[job]->append(temp);
            costs[job]->append(tierCost(tierpos, minimum));
        }
    }

    commands[6] = Berserk;
    QVector<int> *jobs4 = new QVector<int>({
        9, 10, 11, 12, 16, 17, 18,
        1,  2, 13, 14, 15, 19,
        0,  3,  4,  5,  7,  8, 15
    });
    for (int i = 0; i < jobs4->count(); i++) {
        int job = jobs4->at(i);
        Skill temp = actions->first();
        actions->removeFirst();
        commands[job] = temp;
    }
}

QByteArray be24(int num) {
    QByteArray temp;
    temp.append((num >> 16) & 0xFF);
    temp.append((num >> 8) & 0xFF);
    temp.append(num & 0xFF);
    return temp;
}
QByteArray le24(int num) {
    QByteArray temp;
    temp.append(num & 0xFF);
    temp.append((num >> 8) & 0xFF);
    temp.append((num >> 16) & 0xFF);
    return temp;
}

QBuffer *Randomizer::writePatch(void) {
    QBuffer *patch = new QBuffer();
    patch->open(QIODevice::ReadWrite);

    patch->write("PATCH");

    // job commands
    for (int i = 0; i < JOB_COUNT; i++) {
        // skip berserker
        if (i == 6) {
            continue;
        }
        char temp[2];
        temp[0] = commands[i] & 0xFF;
        temp[1] = '\0';
        patch->write(be24(0x15616c + (i * 4) + 1));
        patch->write("\x00\x01", 2);
        patch->write(temp, 1);
    }

    // ability counts
    patch->write(be24(0x14b1fc));
    patch->write("\x00\x14", 2);
    for (int i = 0; i < JOB_COUNT; i++) {
        char count = jobs[i]->count();
        patch->putChar(count);
    }

    // table offset
    patch->write(be24(0x155484));
    patch->write("\x00\x50", 2);
    for (int i = 0; i < JOB_COUNT; i++) {
        QByteArray temp = le24(0x1554e8 + (i * 4*5));
        temp.append('\x08');
        patch->write(temp);
    }

    // ability lists
    patch->write(be24(0x1554E8));
    QByteArray abilities;

    for (int i = 0; i < JOB_COUNT; i++) {
        QVector<Skill> *job = jobs[i];
        char count = job->count();
        for (int j = 0; j < count; j++) {
            QByteArray data;
            int cost = costs[i]->at(j);

            // cost
            data.append(cost & 0xFF);
            data.append((cost >> 8) & 0xFF);
            // skill
            data.append(job->at(j) & 0xFF);
            data.append((char)0);
            abilities.append(data);
        }
    }
    unsigned short size = abilities.count();
    char csize[3];
    csize[0] = (size >> 8) & 0xFF;
    csize[1] = size & 0xFF;
    csize[2] = NULL;
    patch->write(csize, 2);
    patch->write(abilities);
    patch->write("EOF");
    patch->seek(0);
    return patch;
}

QBuffer *Randomizer::makeRandom(bool global_innates) {
    setupData(global_innates);
    randomizeSkills();
    return writePatch();
}
