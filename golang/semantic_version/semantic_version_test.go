package main

import (
	"fmt"
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"

	"github.com/Masterminds/semver"
	mod_semver "golang.org/x/mod/semver"
)

func TestSemver0(t *testing.T) {
	// "golang.org/x/mod/semver" 에서는 버전명은 v로 시작해야지 된다.
	assert.Equal(t, false, mod_semver.IsValid("a.b.c"))
	assert.Equal(t, false, mod_semver.IsValid("1"))
	assert.Equal(t, false, mod_semver.IsValid("1.0"))
	assert.Equal(t, false, mod_semver.IsValid("1.0.0"))
	assert.Equal(t, false, mod_semver.IsValid("1.0.0-rc.0"))
	assert.Equal(t, true, mod_semver.IsValid("v1"))
	assert.Equal(t, true, mod_semver.IsValid("v1.0"))
	assert.Equal(t, true, mod_semver.IsValid("v1.0.0"))
	assert.Equal(t, false, mod_semver.IsValid("v1a.0"))

	// "github.com/Masterminds/semver" 에서는 v 로 시작하지 않아도 된다.
	_, err := semver.NewVersion("1.2.3-beta.1+build345")
	assert.Equal(t, nil, err)
	_, err = semver.NewVersion("a.b.c")
	assert.NotEqual(t, nil, err)
	_, err = semver.NewVersion("1")
	assert.Equal(t, nil, err)
	_, err = semver.NewVersion("1.0")
	assert.Equal(t, nil, err)
	_, err = semver.NewVersion("1.0.0")
	assert.Equal(t, nil, err)
	_, err = semver.NewVersion("1.0.0-rc.0")
	assert.Equal(t, nil, err)
	_, err = semver.NewVersion("v1")
	assert.Equal(t, nil, err)
	_, err = semver.NewVersion("v1.0")
	assert.Equal(t, nil, err)
	_, err = semver.NewVersion("v1.0.0")
	assert.Equal(t, nil, err)
	_, err = semver.NewVersion("v1a.0")
	assert.NotEqual(t, nil, err)
}

func TestSemver1(t *testing.T) {
	// "golang.org/x/mod/semver" 는 비버전인 경우 구분안된다.
	versions := []string{"1.0", "v1", "1.2.3.4", "1.2.3-x.y.1", "a.b.c"}
	fmt.Println("before sort versions", versions)
	mod_semver.Sort(versions)
	fmt.Println("after sort versions", versions)
	assert.Equal(t, "v1", versions[len(versions)-1])

	// "github.com/Masterminds/semver" NewVersion semantic version 여부를 구분할 수 있다.
	raw := []string{"1.2.3", "1.0", "1.3", "2", "0.4.2", "a.b.c", "2.0.0-rc.1", "2.0.0-fix.1"}
	fmt.Println("before sort versions", raw)
	vs := []*semver.Version{}
	for _, r := range raw {
		v, err := semver.NewVersion(r)
		if err != nil {
			// t.Errorf("Error parsing version: %s", err)
			continue
		}
		vs = append(vs, v)
	}
	sort.Sort(semver.Collection(vs))
	fmt.Println("after sort versions", vs)
	assert.Equal(t, "2.0.0", vs[len(vs)-1].String())
}
