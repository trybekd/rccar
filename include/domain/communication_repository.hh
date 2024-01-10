#ifndef COMMUNICATION_REPOSITORY_H
#define COMMUNICATION_REPOSITORY_H

#include "message.hh"

template <typename T>
concept is_message = requires() {
  {(message)T()};
};

template <typename T>
concept communication_repository = requires(T t) {
  {t.read_message()} -> is_message;
};

#endif // COMMUNICATION_REPOSITORY_H
