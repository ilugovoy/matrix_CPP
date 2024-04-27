#!/bin/bash

COMMAND=""
OS_TYPE=""
tool_check="check"
tool_lcov="lcov"
tool_gcov="gcov"
tool_gtest="libgtest-dev"
tool_gmock="libgmock-dev"
tool_tbb="libtbb-dev"
tool_pkgconfig="pkg-config"

# Определение типа операционной системы
case "$(uname)" in
  "Darwin")
    echo "ОС: MacOS"
    OS_TYPE="MacOS"
    COMMAND="brew install"
    ;;
  "Linux")
    echo "ОС: Linux"
    OS_TYPE="Linux"
    COMMAND=" apt install -y"  # -y для автоматического подтверждения установки без запросов
    ;;
  *)
    echo "Операционная система не поддерживается."
    exit 1
    ;;
esac

# Проверяем clang-format
if ! command -v clang-format &> /dev/null; then
  echo "Утилита clang-format не установлена."
  read -p "Хотите установить утилиту clang-format? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
       apt update
      $COMMAND clang-format
      echo "Утилита clang-format установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      $COMMAND clang-format
      echo "Утилита clang-format установлена."
    fi
  else
    echo "Утилита clang-format не будет установлена."
  fi
else
  echo "Утилита clang-format уже установлена."
fi

# Проверяем check на MacOS
if [ "$OS_TYPE" == "MacOS" ]; then
  if pkg-config --modversion check &> /dev/null; then
    echo "Утилита $tool_check уже установлена."
  else
    echo "Утилита $tool_check не установлена."
    read -p "Хотите установить утилиту $tool_check? [y/n] " response
    if [ "$response" == "y" ]; then
      $COMMAND $tool_check
      echo "Утилита $tool_check установлена."
    else
      echo "Утилита $tool_check не будет установлена."
    fi
  fi
fi

# Проверяем check на Linux
if [ "$OS_TYPE" == "Linux" ]; then
  if dpkg -s check &> /dev/null; then
    echo "Утилита $tool_check уже установлена."
  else
    echo "Утилита $tool_check не установлена."
    read -p "Хотите установить утилиту $tool_check? [y/n] " response
    if [ "$response" == "y" ]; then
       apt-get update
      $COMMAND $tool_check
      echo "Утилита $tool_check установлена."
    else
      echo "Утилита $tool_check не будет установлена."
    fi
  fi
fi

# Проверяем lcov
if ! command -v $tool_lcov &> /dev/null; then
  echo "Утилита $tool_lcov не установлена."
  read -p "Хотите установить утилиту $tool_lcov? [y/n] " response
  if [ "$response" == "y" ]; then
    # Команды для установки утилиты
    if [ "$OS_TYPE" == "Linux" ]; then
       apt-get update
    fi
      $COMMAND $tool_lcov
      echo "Утилита $tool_lcov установлена."
  else
    echo "Утилита $tool_lcov не будет установлена."
  fi
else
  echo "Утилита $tool_lcov уже установлена."
fi

# Проверяем gcov
if ! command -v $tool_gcov &> /dev/null; then
  echo "Утилита $tool_gcov не установлена."
  read -p "Хотите установить утилиту $tool_gcov? [y/n] " response
  if [ "$response" == "y" ]; then
    # Команды для установки утилиты
    if [ "$OS_TYPE" == "Linux" ]; then
       apt-get update
    fi
	if [ "$OS_TYPE" == "MacOS" ]; then
      xcode-select --install
    fi
	  $COMMAND $tool_gcov
      echo "Утилита $tool_gcov установлена."
  else
    echo "Утилита $tool_gcov не будет установлена."
  fi
else
  echo "Утилита $tool_gcov уже установлена."
fi

# Проверяем cppcheck
if ! command -v cppcheck &> /dev/null; then
  echo "Утилита cppcheck не установлена."
  read -p "Хотите установить утилиту cppcheck? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
       apt-get update
       apt-get install -y cppcheck
      echo "Утилита cppcheck установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      brew install cppcheck
      echo "Утилита cppcheck установлена."
    fi
  else
    echo "Утилита cppcheck не будет установлена."
  fi
else
  echo "Утилита cppcheck уже установлена."
fi


# Проверяем Doxygen
if ! command -v doxygen &> /dev/null; then
  echo "Утилита Doxygen не установлена."
  read -p "Хотите установить утилиту Doxygen? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
       apt-get update
      $COMMAND doxygen
      echo "Утилита Doxygen установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      brew install doxygen
      echo "Утилита Doxygen установлена."
    fi
  else
    echo "Утилита Doxygen не будет установлена."
  fi
else
  echo "Утилита Doxygen уже установлена."
fi

# Проверяем установку Graphviz
if ! command -v dot &> /dev/null; then
  echo "Утилита Graphviz (dot) не установлена."
  read -p "Хотите установить утилиту Graphviz? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
       apt-get update
      $COMMAND graphviz
      echo "Утилита Graphviz установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      brew install graphviz
      echo "Утилита Graphviz установлена."
    fi
  else
    echo "Утилита Graphviz не будет установлена."
  fi
else
  echo "Утилита Graphviz уже установлена."
fi

# Проверяем установку libgtest-dev
if ! dpkg -s $tool_gtest &> /dev/null; then
  echo "Утилита $tool_gtest не установлена."
  read -p "Хотите установить утилиту $tool_gtest? [y/n] " response
  if [ "$response" == "y" ]; then
    $COMMAND $tool_gtest
    echo "Утилита $tool_gtest установлена."
  else
    echo "Утилита $tool_gtest не будет установлена."
  fi
else
  echo "Утилита $tool_gtest уже установлена."
fi

# Проверяем установку libgmock-dev
if ! dpkg -s $tool_gmock &> /dev/null; then
  echo "Утилита $tool_gmock не установлена."
  read -p "Хотите установить утилиту $tool_gmock? [y/n] " response
  if [ "$response" == "y" ]; then
    $COMMAND $tool_gmock
    echo "Утилита $tool_gmock установлена."
  else
    echo "Утилита $tool_gmock не будет установлена."
  fi
else
  echo "Утилита $tool_gmock уже установлена."
fi

# Проверяем установку libtbb-dev
if ! dpkg -s $tool_tbb &> /dev/null; then
  echo "Утилита $tool_tbb не установлена."
  read -p "Хотите установить утилиту $tool_tbb? [y/n] " response
  if [ "$response" == "y" ]; then
    $COMMAND $tool_tbb
    echo "Утилита $tool_tbb установлена."
  else
    echo "Утилита $tool_tbb не будет установлена."
  fi
else
  echo "Утилита $tool_tbb уже установлена."
fi