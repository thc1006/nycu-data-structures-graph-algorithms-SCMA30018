# NYCU Data Structures & Graph Algorithms (SCMA30018)

[![Build and Test](https://github.com/thc1006/nycu-data-structures-graph-algorithms-SCMA30018/actions/workflows/ci.yml/badge.svg)](https://github.com/thc1006/nycu-data-structures-graph-algorithms-SCMA30018/actions/workflows/ci.yml)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

## 🏫 Course Information | 課程資訊

**國立陽明交通大學 114-1「資料結構與圖論演算法」**  
**NYCU 114-1 Data Structures & Graph Algorithms**

- **課程代碼 Course Code**: 536715  
- **永久課號 Permanent Code**: SCMA30018  
- **學分 Credits**: 3  
- **語言 Language**: C/C++  

## 📋 Repository Contents | 倉庫內容

This repository contains implementations, assignments, and performance analysis for data structures and graph algorithms coursework, featuring:

本倉庫包含資料結構與圖論演算法課程的實作、作業與效能分析，特色包括：

### 🏗️ Project Structure | 專案結構
```
├── src/                    # Source code | 源碼
│   ├── date.h             # Date type header | 日期型別標頭檔
│   ├── date.c             # Date implementation | 日期實作
│   └── main.c             # Demo program | 示範程式
├── tests/                  # Unit tests | 單元測試
│   └── test_date.c        # Date type tests | 日期型別測試
├── benchmarks/             # Performance tests | 效能測試
│   └── bench_date.c       # Date benchmarks | 日期效能測試
├── textbook/               # Course materials | 課程教材  
│   ├── API.md             # API documentation | API 文件
│   ├── outline.pdf        # Course outline | 課程大綱
│   └── p1.pdf             # Chapter 1 materials | 第一章教材
├── examples/               # C programming examples | C程式範例
│   ├── 0a-gcd.c           # GCD algorithm | 最大公因數演算法
│   ├── 0b-div.c           # Division operations | 除法運算
│   ├── 0g-pointer.c       # Pointer manipulation | 指標操作
│   ├── 0h-matrix.c        # Matrix operations | 矩陣運算
│   ├── 0i-Stack.C         # Stack implementation (C++) | 堆疊實作 (C++)
│   ├── 0j-stack.c         # Stack implementation (C) | 堆疊實作 (C)
│   └── ... more examples  # Additional examples | 更多範例
├── .github/workflows/      # CI/CD pipeline | 持續整合
└── Makefile               # Build system | 建置系統
```

## 🚀 Quick Start | 快速開始

### Prerequisites | 前置需求
- GCC or Clang compiler
- Make build system
- Linux/Unix environment (Ubuntu recommended)

### Build and Run | 建置與執行
```bash
# Clone the repository | 複製倉庫
git clone https://github.com/thc1006/nycu-data-structures-graph-algorithms-SCMA30018.git
cd nycu-data-structures-graph-algorithms-SCMA30018

# Build all components | 建置所有元件
make all

# Run demo program | 執行示範程式
make run

# Run unit tests | 執行單元測試
make test

# Run benchmarks | 執行效能測試
make benchmark

# Clean build files | 清理建置檔案
make clean
```

## 🔧 Development | 開發

### Available Commands | 可用指令
```bash
make help          # Show all available commands | 顯示所有可用指令
make all           # Build main executable | 建置主要執行檔
make test          # Build and run tests | 建置並執行測試
make benchmark     # Build and run benchmarks | 建置並執行效能測試
make run           # Build and run demo | 建置並執行示範
make clean         # Remove build files | 移除建置檔案
```

### Testing | 測試
- **Unit Tests**: 42 comprehensive test cases | 42個全面測試案例
- **Memory Testing**: Valgrind integration | Valgrind 整合
- **Performance Testing**: Detailed benchmarks | 詳細效能測試
- **CI/CD**: Automated testing on Ubuntu | Ubuntu 自動化測試

## 📖 Documentation | 文件

- **[API Documentation](docs/API.md)**: Complete function reference | 完整函數參考
- **[Examples](examples/)**: Sample input/output files | 範例輸入/輸出檔案
- **Code Comments**: Inline documentation | 內聯文件註解

## 🤝 Contributing | 貢獻

This repository is for educational purposes. For course-related submissions:

本倉庫用於教育目的。課程相關提交：

1. Fork the repository | 分叉倉庫
2. Create feature branch | 創建功能分支
3. Follow coding standards | 遵循編碼標準
4. Add comprehensive tests | 添加全面測試
5. Submit pull request | 提交拉取請求

## 📄 License | 授權

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

本專案採用 Apache License 2.0 授權 - 詳見 [LICENSE](LICENSE) 檔案。

## 🏷️ Keywords | 關鍵字

**Programming**: C, Data Structures, Algorithms, Graph Theory, Date Handling, Performance Optimization  
**程式設計**: C語言, 資料結構, 演算法, 圖論, 日期處理, 效能最佳化

**Education**: NYCU, Computer Science, Programming Assignment, Unit Testing, Benchmarking  
**教育**: 陽明交通大學, ,應用數學, 資訊工程, 程式作業, 單元測試, 效能評測

**Technical**: ISO 8601, Leap Year, Calendar Algorithm, Memory Management, CI/CD  

---

**National Yang Ming Chiao Tung University | 國立陽明交通大學**  
**Department of Computer Science | 資訊工程學系**  
**Course: Data Structures & Graph Algorithms | 課程：資料結構與圖論演算法**
