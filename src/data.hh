enum Job {
    Passages = 0x01,
    Pitfalls = 0x02,
    LiteStep = 0x04,
    Dash     = 0x08,
    Learning = 0x10
};

const long int job_innates = 0x156138;
const long int monster_block = 0x14D228;
const long int form_block = 0x14FAA8;
// XP Offset = 14D234 - 14D228 = 0xC
// XP little-endian;  0xC D
// Gil little-endian; 0xE F
