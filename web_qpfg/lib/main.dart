import 'package:animations/animations.dart';
import 'package:flutter/material.dart';
import 'package:web_qpfg/qpfg.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Visualize - Yelson',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: '> :  Visualize - Yelson'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);
  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Container(
              child: OpenContainer(
                  closedColor: Colors.transparent,
                  closedElevation: 0,
                  openColor: Colors.transparent,
                  openElevation: 0,
                  closedBuilder: (BuildContext _, VoidCallback openContainer) {
                    return Card(
                      color: Colors.grey.withAlpha(10),
                      // elevation: 0.3,
                      child: Container(
                          height: 50,
                          width: 200,
                          padding: const EdgeInsets.symmetric(
                              horizontal: 20, vertical: 10),
                          child: Center(
                              child: Text(
                            "棋盘覆盖",
                            style: TextStyle(color: Colors.white, fontSize: 18),
                          ))),
                    );
                  },
                  openBuilder: (BuildContext context, VoidCallback _) {
                    return const QPFG();
                  }),
            )
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {},
        tooltip: 'Just nothing ~.~',
        child: const Icon(Icons.add),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }
}
