#include "Common.h"

using namespace r15;

template <typename T>
VARSIZE Tree<T>::regChild(PShared<T> child) {
    childs.push_back(child);

    // Maybe not needed
    return (childs.size() - 1);
}

template <typename T>
PWeak<T> Tree<T>::getChild(VARSIZE id) const {
    return PWeak<T>(childs[id]);
}

// ----

template <typename For>
BOOL TreeHandler<For>::canHandle(For what) {
    stackChildCall(
        &SpecificHandler<For>::canHandle,
        True,
        &bool::operator|=,
        what
    );
}