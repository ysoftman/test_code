import React from "react";

const MyComp1 = (props) => {
  const { command, result } = props;
  return (
    // 2개이상일 경우 React.Fragment (또는 div 등올) 감싸야야 한다.
    // 상위 css 스타일을 사용하기 위해선 React.Fragment 사용
    <React.Fragment>
      <h2>command={command}</h2>
      <h2>result={result}</h2>
    </React.Fragment>
  );
};
export default MyComp1;
