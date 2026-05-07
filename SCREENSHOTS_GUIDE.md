# Screenshots Guide - How to Capture Program Output

**For**: CSF303 Practical 6 - Advanced Algorithms  
**Date**: 7 May 2026

---

## Quick Summary

This guide explains how to take screenshots of the program output to include in your submission.

---

## Step-by-Step Instructions

### Step 1: Compile and Run the Program

```bash
cd /Users/tsheringwangpodorji/Documents/Year3\ Sem\ II/CSF303/AS2026_CSF303_Practical6

# Clean and compile
make clean
make

# Run the program
./algorithms
```

### Step 2: Take Screenshot

#### **On macOS (Easiest)**:

1. **Method A: Screenshot Entire Window**
   - Run: `./algorithms`
   - Let output display in terminal
   - Press: `Command + Shift + 4`
   - Then press: `Spacebar`
   - Click on the terminal window
   - Screenshot automatically saves to Desktop
   - Move file to `screenshots/` folder and rename to `output_screenshot.png`

2. **Method B: Screenshot Specific Area**
   - Press: `Command + Shift + 4`
   - Drag to select the output area
   - Screenshot saves to Desktop
   - Move to `screenshots/` folder

3. **Method C: Using Print Screen**
   - Run: `./algorithms`
   - Press: `Print Screen` (or `Fn + Shift + 3` for whole screen)
   - Or: `Fn + Shift + 4` for partial screenshot

#### **On Linux**:

1. **Using Print Screen**
   - Run: `./algorithms`
   - Press: `Print Screen` to capture whole window
   - Or: `Shift + Print Screen` for selection
   - Or use: `screenshot` tool

2. **Using gnome-screenshot**
   ```bash
   gnome-screenshot -w  # Capture window only
   gnome-screenshot -a  # Capture area
   ```

#### **Alternative: Save Output to Text File**

If screenshots are difficult, save the output to a text file:

```bash
./algorithms > program_output.txt

# Then screenshot the text file, or attach it directly
cat program_output.txt
```

---

## What to Screenshot

### Option 1: Full Program Execution

Screenshot showing the entire program output from start to finish.

**What it should show**:

- Program title/header
- All three algorithms running
- Test cases and results
- Completion message

### Option 2: Individual Algorithm Screenshots

Take 3 separate screenshots for each algorithm:

**Screenshot 1: Trie Operations**

- Shows: INSERT, SEARCH, PREFIX CHECK, DELETE operations
- Evidence of: String storage and retrieval working

**Screenshot 2: PATRICIA Operations**

- Shows: INSERT with edge compression, SEARCH, DELETE
- Evidence of: Compressed trie structure working

**Screenshot 3: Manacher's Algorithm**

- Shows: Palindrome finding tests and verification
- Evidence of: O(n) algorithm finding correct results

### Option 3: Compilation + Execution

Take screenshots showing:

1. `make clean && make` → Shows successful compilation
2. `./algorithms` → Shows program output

---

## Where to Save Screenshots

### Create screenshots folder (if not exists):

```bash
mkdir -p /Users/tsheringwangpodorji/Documents/Year3\ Sem\ II/CSF303/AS2026_CSF303_Practical6/screenshots
```

### Save screenshots with these names:

```
screenshots/
├── output_screenshot.png          (Main program output)
├── trie_operations.png            (Optional: Trie demo)
├── patricia_operations.png        (Optional: PATRICIA demo)
└── manacher_algorithm.png         (Optional: Manacher demo)
```

---

## Evidence Without Screenshots

**If you cannot take screenshots**, the project includes:

1. **`output.txt`** - Complete text output of all operations
   - Shows all algorithm results
   - Can be attached directly to submission
   - Can be screenshotted if needed

2. **Program execution** - Run `./algorithms` anytime
   - Code is compiled and ready
   - All tests pass and execute cleanly

---

## Verifying Your Screenshot

Your screenshot should clearly show:

✓ **Trie Section**:

- Multiple insertions (apple, app, application, etc.)
- Searches finding/not finding words
- Deletions working correctly
- Prefix checks passing

✓ **PATRICIA Section**:

- Insertions with compression
- All searches successful
- Deletions with edge reconstruction

✓ **Manacher Section**:

- Multiple palindrome test cases
- Correct longest palindrome found
- Verification against brute force (✓ match)

---

## Sample Output You'll See

```
============================================================
        CSF303 PRACTICAL 6: ADVANCED ALGORITHMS
============================================================

========== TRIE IMPLEMENTATION ==========

--- INSERT OPERATIONS ---
✓ Inserted: apple
✓ Inserted: app
✓ Inserted: application
... (more operations)

========== PATRICIA TREE IMPLEMENTATION ==========

--- INSERT OPERATIONS ---
✓ Inserted: apple
... (more operations)

========== MANACHER'S ALGORITHM IMPLEMENTATION ==========

--- Input: "babad" ---
Longest Palindrome: "bab"
Length: 3
... (more operations)

============================================================
              DEMONSTRATION COMPLETED
============================================================
```

---

## Submission Package Structure

Your final submission should have:

```
AS2026_CSF303_Practical6/
│
├── CODE FILES (REQUIRED)
│   ├── main.cpp
│   ├── trie.cpp
│   ├── patricia.cpp
│   └── manacher.cpp
│
├── BUILD (REQUIRED)
│   ├── Makefile
│   └── algorithms (executable)
│
├── DOCUMENTATION (REQUIRED)
│   ├── README.md                    (Implementation report)
│   ├── REFLECTION.md                (Technical reflection)
│   └── SCREENSHOTS_GUIDE.md         (This file)
│
├── EVIDENCE (REQUIRED)
│   ├── output.txt                   (Program output)
│   └── screenshots/
│       └── output_screenshot.png    (Screenshot of output)
```

---

## Quick Checklist

- [ ] Compile code: `make clean && make`
- [ ] Run program: `./algorithms`
- [ ] Take screenshot of output
- [ ] Save to: `screenshots/output_screenshot.png`
- [ ] Verify screenshot is readable
- [ ] Include in submission folder

---

## Done!

Once you have your screenshot(s), your submission is complete with all required elements:

- ✓ Code files (\*.cpp)
- ✓ Output screenshot(s)
- ✓ Implementation report (README.md)
- ✓ Reflection (REFLECTION.md)
