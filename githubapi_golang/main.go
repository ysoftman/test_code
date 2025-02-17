package main

import (
	"context"
	"fmt"
	"log"
	"time"

	"github.com/caarlos0/env"
	"github.com/google/go-github/v69/github"
	"golang.org/x/oauth2"
)

type GithubConfig struct {
	Owner      string `env:"OWNER" envDefault:""`
	Token      string `env:"TOKEN" envDefault:""`
	Repository string `env:"REPOSITORY" envDefault:""`
	BaseBranch string `env:"BASE_BRANCH" envDefault:""`
}

type Github struct {
	Owner      string
	Token      string
	Repository string
	BaseBranch string
	Client     *github.Client
}

func NewGithub(owner, token, repository, baseBranch string) *Github {
	ts := oauth2.StaticTokenSource(&oauth2.Token{AccessToken: token})
	tc := oauth2.NewClient(context.Background(), ts)
	// for enterprise github
	// client, err := github.NewClient(tc).WithEnterpriseURLs("https://ysoftman.github.com", "https://ysoftman.github.com")
	// for github.com
	client := github.NewClient(tc)
	return &Github{
		Owner:      owner,
		Token:      token,
		Repository: repository,
		BaseBranch: baseBranch,
		Client:     client,
	}
}

func (gh *Github) CheckBranchOrCreate(branchName string) error {
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel()

	_, _, err := gh.Client.Repositories.GetBranch(ctx, gh.Owner, gh.Repository, branchName, 1)
	if err == nil {
		return nil
	}

	baseRef, _, err := gh.Client.Git.GetRef(ctx, gh.Owner, gh.Repository, "refs/heads/"+gh.BaseBranch)
	if err != nil {
		return fmt.Errorf("failed to get base branch reference: %v", err)
	}

	newRef := &github.Reference{
		Ref: github.Ptr("refs/heads/" + branchName),
		Object: &github.GitObject{
			SHA: baseRef.Object.SHA,
		},
	}

	_, _, err = gh.Client.Git.CreateRef(ctx, gh.Owner, gh.Repository, newRef)
	if err != nil {
		return fmt.Errorf("failed to create new branch: %v", err)
	}

	return nil
}

func (gh *Github) CheckFirstCommitOrCreate() error {
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel()

	// "409 Git Repository is empty."
	// This error is common when working with newly created repositories that have not been initialized with any commits
	// check if commit exists
	_, _, err := gh.Client.Git.GetRef(ctx, gh.Owner, gh.Repository, "refs/heads/"+gh.BaseBranch)
	if err == nil {
		return nil
	}

	readmeFile := &github.RepositoryContentFileOptions{
		Message: github.Ptr("initial commit"),
		Content: []byte(fmt.Sprintf("# %s", gh.Repository)),
	}
	_, _, err = gh.Client.Repositories.CreateFile(ctx, gh.Owner, gh.Repository, "README.md", readmeFile)
	if err != nil {
		return fmt.Errorf("failed to create readme file: %v", err)
	}

	return nil
}

func (gh *Github) Commit(branchName string, commitMessage string, fileContents, filePaths []string) error {
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel()

	ref, _, err := gh.Client.Git.GetRef(ctx, gh.Owner, gh.Repository, "refs/heads/"+branchName)
	if err != nil {
		return fmt.Errorf("failed to get ref: %v", err)
	}

	baseTree, _, err := gh.Client.Git.GetTree(ctx, gh.Owner, gh.Repository, ref.GetObject().GetSHA(), true)
	if err != nil {
		return fmt.Errorf("failed to get base tree: %v", err)
	}
	entries := []*github.TreeEntry{}
	for i := range fileContents {
		entries = append(entries, &github.TreeEntry{
			Path:    github.Ptr(filePaths[i]),
			Type:    github.Ptr("blob"),
			Content: github.Ptr(fileContents[i]),
			Mode:    github.Ptr("100644"),
		})
	}
	newTree, _, err := gh.Client.Git.CreateTree(ctx, gh.Owner, gh.Repository, baseTree.GetSHA(), entries)
	if err != nil {
		return fmt.Errorf("failed to create tree: %v", err)
	}

	latestCommit, _, err := gh.Client.Repositories.GetCommit(ctx, gh.Owner, gh.Repository, branchName, nil)
	if err != nil {
		return fmt.Errorf("failed to get latest commit: %v", err)
	}
	// No changes detected. Skipping commit.
	if *newTree.SHA == *latestCommit.Commit.Tree.SHA {
		fmt.Printf("[branch:%s, commit_message:%s] No changes detected. Skipping commit.\n", branchName, commitMessage)
		return nil
	}

	commit, _, err := gh.Client.Git.CreateCommit(ctx, gh.Owner, gh.Repository, &github.Commit{
		Message: github.Ptr(commitMessage),
		Tree:    newTree,
		Parents: []*github.Commit{{SHA: ref.Object.SHA}},
	}, nil)
	if err != nil {
		return fmt.Errorf("failed to create commit: %v", err)
	}
	_, _, err = gh.Client.Git.UpdateRef(ctx, gh.Owner, gh.Repository, &github.Reference{
		Ref:    github.Ptr("refs/heads/" + branchName),
		Object: &github.GitObject{SHA: commit.SHA},
	}, false)
	if err != nil {
		return fmt.Errorf("failed to update ref: %v", err)
	}
	fmt.Printf("[branch:%s, commit_message:%s] committed.\n", branchName, commitMessage)

	return nil
}

func (gh *Github) DeleteBranch(branchName string) error {
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel()
	// check if branch exists
	_, _, err := gh.Client.Repositories.GetBranch(ctx, gh.Owner, gh.Repository, branchName, 1)
	if err != nil {
		fmt.Printf("%s branch does not exists.\n", branchName)
		return nil
	}
	_, err = gh.Client.Git.DeleteRef(ctx, gh.Owner, gh.Repository, "refs/heads/"+branchName)
	if err != nil {
		return fmt.Errorf("failed to delete %s branch: %v", branchName, err)
	}
	fmt.Printf("%s branch is deleted.\n", branchName)

	return nil
}

func main() {
	ghConfig := GithubConfig{}
	if err := env.Parse(&ghConfig); err != nil {
		log.Fatalf("failed to parse environment variables\n%+v\n", ghConfig)
	}
	// fmt.Printf("%+v\n", ghConfig)

	gh := NewGithub(ghConfig.Owner, ghConfig.Token, ghConfig.Repository, ghConfig.BaseBranch)
	if err := gh.CheckFirstCommitOrCreate(); err != nil {
		log.Fatalln(err)
	}
	if err := gh.CheckBranchOrCreate("test1"); err != nil {
		log.Fatalln(err)
	}
	if err := gh.Commit("test1", "this is test", []string{"apple", "banana"}, []string{"apple.txt", "banana.txt"}); err != nil {
		log.Fatalln(err)
	}
	if err := gh.CheckBranchOrCreate("test2"); err != nil {
		log.Fatalln(err)
	}
	if err := gh.Commit("test2", "this is test", []string{"cherry1", "lemon1"}, []string{"cherry.txt", "lemon.txt"}); err != nil {
		log.Fatalln(err)
	}
	// if err := gh.DeleteBranch("test2"); err != nil {
	// 	log.Fatalln(err)
	// }
}
