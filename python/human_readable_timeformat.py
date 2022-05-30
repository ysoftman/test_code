from datetime import datetime, timedelta

# docker cli 참고 https://github.com/docker/cli/blob/master/vendor/github.com/docker/go-units/duration.go#L12
def to_human_readable_timeformat(timestr: str) -> str:
    if timestr is None:
        return None
    d = (
        datetime.utcnow().timestamp()
        - datetime.utcfromtimestamp(
            datetime.strptime(timestr, "%Y-%m-%dT%H:%M:%S%z").timestamp()
        ).timestamp()
    )
    seconds = int(d)
    minutes = int(seconds / 60)
    hours = int(minutes / 60 + 0.5)
    if seconds < 1:
        return "Less than a second"
    elif seconds == 1:
        return "1 second"
    elif seconds < 60:
        return f"{seconds} seconds"
    elif minutes == 1:
        return "About a minute"
    elif minutes < 60:
        return f"{minutes} minutes"
    elif hours == 1:
        return "About an hour"
    elif hours < 48:
        return f"{hours} hours"
    elif hours < 24 * 7 * 2:
        return f"{int(hours/24)} days"
    elif hours < 24 * 30 * 2:
        return f"{int(hours/24/7)} weeks"
    elif hours < 24 * 365 * 2:
        return f"{int(hours/24/30)} months"

    return f"{int(hours/24/365)} years"


print(to_human_readable_timeformat("2010-12-31T17:25:10+09:00"))
# print((datetime.now() - timedelta(days=10)).strftime("%Y-%m-%dT%H:%M:%S+09:00"))
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(weeks=120)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(weeks=50)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(weeks=3)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(days=100)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(days=12)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(hours=5)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(minutes=30)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(seconds=90)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(seconds=59)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(seconds=0.2)).strftime("%Y-%m-%dT%H:%M:%S+09:00")
    )
)
print(
    to_human_readable_timeformat(
        (datetime.now() - timedelta(milliseconds=100)).strftime(
            "%Y-%m-%dT%H:%M:%S+09:00"
        )
    )
)


print("-----test-----")
print("utcnow():", datetime.utcnow())
print("utcnow().timestamp():", datetime.utcnow().timestamp())
print("now():", datetime.now())
print("now().timestamp():", datetime.now().timestamp())
# localtime -> utc
print(
    "utcfromtimestamp(utcnow):",
    datetime.utcfromtimestamp(datetime.utcnow().timestamp()),
)
print("utcfromtimestamp(now):", datetime.utcfromtimestamp(datetime.now().timestamp()))
print(
    "utcfromtimestamp(now+9:00):",
    datetime.utcfromtimestamp(datetime.now().timestamp() + 60 * 60 * 9),
)

print(datetime.strptime("2010-12-31T17:25:10+09:00", "%Y-%m-%dT%H:%M:%S%z").utcoffset())

a = datetime.utcfromtimestamp(
    datetime.strptime("2010-12-31T17:25:10-09:00", "%Y-%m-%dT%H:%M:%S%z").timestamp()
)
print(a)
print(a.timestamp())

a = datetime.utcfromtimestamp(
    datetime.strptime("2010-12-31T17:25:10+09:00", "%Y-%m-%dT%H:%M:%S%z").timestamp()
)
print(a)
print(a.timestamp())

a = datetime.utcfromtimestamp(
    datetime.strptime("2010-12-31T17:25:10Z", "%Y-%m-%dT%H:%M:%S%z").timestamp()
)
print(a)
print(a.timestamp())
