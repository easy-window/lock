# Process Lock Libraries
A library for process lock.

## Usage

```cpp
#include "Lock.h"
using namespace Easy;

CLock::Init(_T("PROCESS_LOCK_NAME"));

CLock::On();

// do something

CLock::Off();

// exit process
CLock::Release();

```
