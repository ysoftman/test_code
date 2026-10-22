import { Suspense, useState, use } from "react";

const cache = new Map();

function fetchUser(id) {
  if (!cache.has(id)) {
    cache.set(
      id,
      new Promise((resolve) => {
        setTimeout(() => resolve({ id, name: `user-${id}`, email: `user${id}@example.com` }), 1000);
      }),
    );
  }
  return cache.get(id);
}

function UserProfile({ userId }) {
  // use() 는 promise 가 resolve 되기 전까지 가장 가까운 Suspense fallback 을 보여준다.
  const user = use(fetchUser(userId));
  return (
    <div>
      <p>name: {user.name}</p>
      <p>email: {user.email}</p>
    </div>
  );
}

function UseExample() {
  const [userId, setUserId] = useState(1);

  return (
    <section className="card">
      <h2>use() + Suspense</h2>
      <p>use() 로 promise 를 렌더링 중에 읽고, Suspense 로 로딩을 처리한다.</p>
      <div className="row">
        {[1, 2, 3].map((id) => (
          <button key={id} type="button" onClick={() => setUserId(id)}>
            user {id}
          </button>
        ))}
      </div>
      <Suspense fallback={<p className="loading">loading user...</p>}>
        <UserProfile userId={userId} />
      </Suspense>
    </section>
  );
}

export default UseExample;
