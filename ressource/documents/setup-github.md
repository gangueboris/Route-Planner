
# How to work with collaborator on github ?

--- 

### **1. Setting Up the Collaboration**
#### **Option 1: Add Collaborators (For Private Repos)**
If you own the repository:
1. Go to your **GitHub repository**.
2. Click on **Settings** > **Collaborators**.
3. Add collaborators by their **GitHub usernames or emails**.
4. They will receive an **invitation** to join the repo.

#### **Option 2: Forking (For Public Repos)**
If you’re working on an **open-source** project:
1. Each collaborator **forks** the repository (copies it to their GitHub).
2. They work on their **forked repo** and submit **pull requests** to the original repository.

---

### **2. Cloning the Repository**
Once invited or working on a forked repo, collaborators need to clone it:
```sh
git clone https://github.com/username/repository.git
cd repository
```
Replace `username/repository` with the actual repo link.

---

### **3. Creating a New Branch**
Collaborators should avoid working directly on the `main` branch:
```sh
git checkout -b feature-branch
```
Example:
```sh
git checkout -b add-login-feature
```

---

### **4. Making Changes and Committing**
Modify files, then commit:
```sh
git add .
git commit -m "Added login feature"
```

---

### **5. Pushing to GitHub**
```sh
git push origin feature-branch
```
This uploads the changes to GitHub.

---

### **6. Creating a Pull Request (PR)**
On GitHub:
1. Go to your repository.
2. Click on **Pull Requests** > **New Pull Request**.
3. Select **compare branch** (your feature branch) and **base branch** (`main` or `develop`).
4. Write a short **title** and **description**.
5. Click **Create Pull Request**.
6. Other team members can **review** and **approve**.

---

### **7. Merging Changes**
After approval, merge the PR:
1. Click **Merge Pull Request**.
2. Delete the branch (optional).

---

### **8. Keeping Your Local Repo Updated**
To get the latest changes:
```sh
git checkout main
git pull origin main
git branch -d feature-branch  # Delete local branch after merge
```

If working on a fork:
```sh
git remote add upstream https://github.com/original-owner/repository.git
git fetch upstream
git merge upstream/main
```

---

### **9. Handling Merge Conflicts**
If Git reports conflicts:
1. Open the conflicting files.
2. Manually resolve conflicts (`<<<< HEAD` marks the conflict area).
3. Add and commit the resolved files:
   ```sh
   git add .
   git commit -m "Resolved merge conflict"
   ```
4. Push the changes.

---

### **10. Using Issues and Discussions**
- Use **GitHub Issues** to track bugs and feature requests.
- Use **GitHub Discussions** for general project discussions.

---

### **Summary of Workflow**
1. **Clone** the repo.
2. **Create** a new branch.
3. **Work** on the branch and commit changes.
4. **Push** the branch and create a **pull request**.
5. **Review and merge** PRs.
6. **Update** your local repo.

