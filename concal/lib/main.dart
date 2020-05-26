import 'dart:ui';

import 'package:flutter/material.dart';

import 'package:flutter_calendar_carousel/flutter_calendar_carousel.dart'
    show CalendarCarousel;
import 'package:flutter_calendar_carousel/classes/event.dart';
import 'package:flutter_calendar_carousel/classes/event_list.dart';
import 'package:intl/intl.dart' show DateFormat;
import 'package:flutter/services.dart';

// void main() => runApp(new MyApp());
void main() {
  WidgetsFlutterBinding.ensureInitialized();
  SystemChrome.setPreferredOrientations(
      [DeviceOrientation.portraitDown, DeviceOrientation.portraitUp]).then((_) {
    runApp(MyApp());
  });
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'concal',
      theme: new ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: new MyHomePage(title: '빵똥구리 달력'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);
  final String title;
  @override
  _MyHomePageState createState() => new _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  // DateTime _currentDate = DateTime(2020, 5, 3);
  DateTime _currentDate = DateTime.now();
  // String _currentMonth = DateFormat.yMMM().format(DateTime(2020, 5, 3));
  String _currentMonth = DateFormat.yMMM().format(DateTime.now());
  // DateTime _targetDateTime = DateTime(2020, 5, 3);
  DateTime _targetDateTime = DateTime.now();
  // List<DateTime> _markedDate = [DateTime(2018, 9, 20), DateTime(2018, 10, 11)];
  static Widget _eventIcon = new Container(
    decoration: new BoxDecoration(
        color: Colors.purple,
        borderRadius: BorderRadius.all(Radius.circular(1000)),
        border: Border.all(color: Colors.blue, width: 5.0)),
    child: new Icon(
      Icons.person,
      color: Colors.amber,
    ),
  );

  EventList<Event> _markedDateMap = new EventList<Event>(
    events: {},
  );

  // CalendarCarousel _calendarCarousel;
  CalendarCarousel _calendarCarouselNoHeader;

  @override
  void initState() {
    // Add more events to _markedDateMap EventList
    // _markedDateMap.add(
    //     new DateTime(2020, 5, 25),
    //     new Event(
    //       date: new DateTime(2020, 5, 25),
    //       title: 'Event 5',
    //       icon: _eventIcon,
    //     ));
    // _markedDateMap.add(
    //     new DateTime(2020, 5, 10),
    //     new Event(
    //       date: new DateTime(2020, 5, 10),
    //       title: 'Event 4',
    //       icon: _eventIcon,
    //     ));
    // _markedDateMap.addAll(new DateTime(2020, 5, 11), [
    //   new Event(
    //     date: new DateTime(2020, 5, 11),
    //     title: 'Event 1',
    //     icon: _eventIcon,
    //   ),
    //   new Event(
    //     date: new DateTime(2020, 5, 11),
    //     title: 'Event 2',
    //     icon: _eventIcon,
    //   ),
    //   new Event(
    //     date: new DateTime(2020, 5, 11),
    //     title: 'Event 3',
    //     icon: _eventIcon,
    //   ),
    // ]);
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    /// Example Calendar Carousel without header and custom prev & next button
    _calendarCarouselNoHeader = CalendarCarousel<Event>(
      onDayPressed: (DateTime date, List<Event> events) {
        this.setState(() => _currentDate = date);
        events.forEach((event) => print(event.title));
      },
      locale: "en",
      markedDatesMap: _markedDateMap,
      weekFormat: false,
      firstDayOfWeek: 1,
      // daysHaveCircularBorder: true,
      showOnlyCurrentMonthDate: true,
      weekDayBackgroundColor: Colors.black,
      weekdayTextStyle: TextStyle(
        fontStyle: FontStyle.normal,
        fontSize: 15,
        color: Colors.white,
      ),
      inactiveDaysTextStyle: TextStyle(
        color: Colors.black,
        fontSize: 28,
      ),
      weekendTextStyle: TextStyle(
        fontStyle: FontStyle.italic,
        fontSize: 28,
        color: Colors.white,
        backgroundColor: Colors.black,
      ),
      inactiveWeekendTextStyle: TextStyle(
        fontStyle: FontStyle.italic,
        fontSize: 28,
        color: Colors.white,
        // backgroundColor: Colors.black,
      ),
      thisMonthDayBorderColor: Colors.white,
      daysTextStyle: TextStyle(
        fontStyle: FontStyle.normal,
        fontSize: 28,
        color: Colors.black,
      ),
      // 이 값을 낮추면 아래에 달력이 하나 더 보인다.
      height: 1000.0,
      selectedDateTime: _currentDate,
      targetDateTime: _targetDateTime,
      customGridViewPhysics: NeverScrollableScrollPhysics(),
      pageScrollPhysics: NeverScrollableScrollPhysics(),
      markedDateCustomShapeBorder:
          CircleBorder(side: BorderSide(color: Colors.greenAccent)),
      markedDateCustomTextStyle: TextStyle(
        fontSize: 28,
        color: Colors.blue,
      ),
      showHeader: true,
      headerTextStyle: TextStyle(
        fontSize: 45.0,
        color: Colors.black,
      ),
      todayBorderColor: Colors.black,
      todayButtonColor: Colors.green,
      todayTextStyle: TextStyle(
        fontSize: 28,
        color: Colors.yellow,
      ),
      markedDateShowIcon: true,
      markedDateIconMaxShown: 5,
      markedDateIconBuilder: (event) {
        return event.icon;
      },
      markedDateMoreShowTotal: true,
      // selectedDayBorderColor: Colors.black,
      selectedDayButtonColor: Colors.black,
      selectedDayTextStyle: TextStyle(
        fontSize: 28,
        color: Colors.yellow,
        // backgroundColor: Colors.black,
      ),
      minSelectedDate: _currentDate.subtract(Duration(days: 360)),
      maxSelectedDate: _currentDate.add(Duration(days: 360)),
      prevDaysTextStyle: TextStyle(
        fontSize: 28,
        color: Colors.pinkAccent,
      ),
      onCalendarChanged: (DateTime date) {
        this.setState(() {
          _targetDateTime = date;
          _currentMonth = DateFormat.yMMM().format(_targetDateTime);
        });
      },
      onDayLongPressed: (DateTime date) {
        print('long pressed date $date');
      },
    );

    return new Scaffold(
        appBar: new AppBar(
          title: new Text(widget.title),
        ),
        body: SingleChildScrollView(
          physics: NeverScrollableScrollPhysics(),
          child: Column(
            // crossAxisAlignment: CrossAxisAlignment.start,
            // mainAxisAlignment: MainAxisAlignment.start,
            children: <Widget>[
              FlatButton(
                // color: Colors.greenAccent,
                child: Text(
                  '오늘',
                  style: TextStyle(fontSize: 30),
                ),
                onPressed: () {
                  setState(() {
                    _targetDateTime = DateTime.now();
                    _currentDate = _targetDateTime;
                    _currentMonth = DateFormat.yMMM().format(_targetDateTime);
                  });
                },
              ),
              _calendarCarouselNoHeader,
            ],
          ),
        ));
  }
}
