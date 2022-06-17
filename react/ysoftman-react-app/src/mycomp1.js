import React from 'react';

const MyComp1 = (props) => {
    const { param1, param2 } = props
    return (
        // 2개이상일 경우 React.Fragment (또는 div 등올) 감싸야야 한다.
        // 상위 css 스타일을 사용하기 위해선 React.Fragment 사용
        <React.Fragment>
            <header>
                <h1>parm1={param1}</h1>
                <h2>parm2={param2}</h2>
            </header>
        </React.Fragment>
    )
}
export default MyComp1;
