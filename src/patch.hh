
#pragma once

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QString>

enum PatchType {
	Mode,
	NED,
};


QList<QPair<QString,QString> > getPatchList(QDir dir, PatchType type);