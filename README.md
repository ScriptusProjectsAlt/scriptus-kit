<div align="center">

<h1>SCRIPTKIT</h1>

<p>
  <strong>User Level Rootkit that injects into explorer.exe making the code look like a trusted program.</strong>
</p>

<p>
  Lightweight • Educational • Terminal Based
</p>

<img src="https://img.shields.io/badge/status-experimental-red?style=for-the-badge">
<img src="https://img.shields.io/badge/python-3.10+-red?style=for-the-badge&logo=python">
<img src="https://img.shields.io/badge/platform-windows%20%7C%20linux-red?style=for-the-badge">
<img src="https://img.shields.io/badge/version-0.0.1-red?style=for-the-badge">

</div>

---

## Overview

**scriptus-kit** is a Python-based user level rootkit but injects into explorer.exe to elevate permissions bypassing whitelisted maleware where the process is trusted like "convhost" or "explorer.exe"

It is intended for **experimenting / learning**.

---

## notice

- The **scriptkit.dll** is the 

---

## Installation

```bash
git clone https://github.com/yourname/scriptus-kit.git
cd scriptus-kit
pip install -r requirements.txt
```

---

## Usage

### Process listing

```bash
scriptus --processes
```

### Network overview

```bash
scriptus --network
```

### System snapshot

```bash
scriptus --snapshot
```

---

## Notes

```
[!] Designed for educational use only
[!] Do not use on systems without permission
[!] Avoid modifying system-critical processes
```

---

## Disclaimer

This project is intended for learning purposes only. Unauthorized use on systems you do not own or have permission to analyze may violate laws or policies.
