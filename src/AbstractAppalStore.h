#pragma once

#include <QPoint>
#include <QList>

class AbstractAppalStore {
public:
    virtual QList<QPoint> getAllAppalsPos() const = 0;

    virtual ~AbstractAppalStore() = default;
};
