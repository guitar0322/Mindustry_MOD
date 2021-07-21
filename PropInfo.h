#pragma once

#define CATEGORY_NUM 4
#define PROP_MAX 2
#define TURRET 0
#define PRODUCTION 1
#define RAIL 2
#define DEFENSE 3

enum PROPDIR {
    RIGHT,
    DOWN,
    LEFT,
    UP
};

typedef struct tagLink {
    bool isConnect; //true면 연결 false면 미연결
    bool inOut; //true면 out false면 in
}LINK;

inline vector<pair<int, int>> GetDrillTile(int tileX, int tileY)
{
    vector<pair<int, int>> result;
    result.push_back({ tileX ,tileY });
    result.push_back({ tileX - 1, tileY });
    result.push_back({ tileX, tileY - 1 });
    result.push_back({ tileX - 1, tileY - 1 });

    return result;
}

