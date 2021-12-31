import 'dart:async';
import 'dart:math';

import 'package:flutter/material.dart';
import 'package:numberpicker/numberpicker.dart';

List<Color?> cols = [
  Colors.blue[100],
  Colors.blue[200],
  Colors.blue[300],
  Colors.blue[400],
  Colors.blue,
  Colors.blue[600],
  Colors.blue[700],
  Colors.blue[800],
  Colors.blue[900],
];

class QPFG extends StatefulWidget {
  const QPFG({Key? key}) : super(key: key);

  @override
  _QPFGState createState() => _QPFGState();
}

class _QPFGState extends State<QPFG> {
  bool is_start = false;
  int _counter = 1;
  int _px = 1, _py = 1;
  List<List<int>> matrix = [
    [0, 0, 0],
    [0, -1, 0],
    [0, 0, 0],
  ];

  //通过设置异步函数延时时间来实现覆盖动画
  int dd = 0;

  void draw(int px, int py, int nx, int ny, int dep) {
    Future.delayed(Duration(milliseconds: (dd += 100)), () {
      //延时执行的代码
      setState(() {
        for (int i = 0; i <= 1; i++) {
          for (int j = 0; j <= 1; j++) {
            if (nx + i != px || ny + j != py) {
              matrix[nx + i][ny + j] = dep;
            }
          }
        }
      });
    });
  }

  //矩阵阶数n，障碍物坐标px，障碍物坐标py，当前矩阵左上角坐标nx，当前矩阵左上角坐标ny.
  void divideConquer(int n, int px, int py, int nx, int ny) {
    if (n == 1) {
      draw(px, py, nx, ny, n);
      return;
    }
    int len = 1 << (n - 1), flag = 0;
    List<int> x = [0, nx + len - 1, nx + len - 1, nx + len, nx + len];
    List<int> y = [0, ny + len - 1, ny + len, ny + len - 1, ny + len];

    //area1
    if (nx <= px && px <= nx + len - 1 && ny <= py && py <= ny + len - 1) {
      flag = 1;
    } else if (nx <= px &&
        px <= nx + len - 1 &&
        ny + len <= py &&
        py <= ny + 2 * len - 1) {
      flag = 2;
    } else if (nx + len <= px &&
        px <= nx + 2 * len - 1 &&
        ny <= py &&
        py <= ny + len - 1) {
      flag = 3;
    } else if (nx + len <= px &&
        px <= nx + 2 * len - 1 &&
        ny + len <= py &&
        py <= ny + 2 * len - 1) {
      flag = 4;
    }

    int dx = 0, dy = 0;
    for (int i = 1; i <= 4; i++) {
      if (flag == i) {
        dx = x[i];
        dy = y[i];
        x[i] = px;
        y[i] = py;
      }
    }
    draw(dx, dy, nx + len - 1, ny + len - 1, n);

    divideConquer(n - 1, x[1], y[1], nx, ny);
    divideConquer(n - 1, x[2], y[2], nx, ny + len);
    divideConquer(n - 1, x[3], y[3], nx + len, ny);
    divideConquer(n - 1, x[4], y[4], nx + len, ny + len);
  }

  void _start() {
    is_start = true;
    dd = 0;
    int size = 1 << _counter;
    matrix =
        List.generate(size + 1, (_) => List.generate(size + 1, (index) => 0));
    matrix[_px][_py] = -1;
    setState(() {});
    divideConquer(_counter, _px, _py, 1, 1);
    Future.delayed(Duration(milliseconds: (dd += 100)), () {
      setState(() {
        is_start = false;
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    double pm_size = MediaQuery.of(context).size.height;

    return Scaffold(
      appBar: AppBar(
        title: const Text("棋盘覆盖"),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          mainAxisSize: MainAxisSize.min,
          children: [
            Text('棋盘阶数', style: Theme.of(context).textTheme.headline6),
            NumberPicker(
              value: _counter,
              minValue: 1,
              maxValue: 5,
              step: 1,
              itemHeight: 40,
              axis: Axis.horizontal,
              onChanged: (value) => setState(() => _counter = value),
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(10),
                border: Border.all(color: Colors.black26),
              ),
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                IconButton(
                  icon: Icon(Icons.remove),
                  onPressed: () {
                    if (!is_start) {
                      setState(() {
                        final newValue = _counter - 1;
                        _counter = newValue.clamp(1, 5);
                        int size = 1 << _counter;
                        matrix = List.generate(size + 1,
                            (_) => List.generate(size + 1, (index) => 0));
                        _px = min(_px, size);
                        _py = min(_py, size);
                        matrix[_px][_py] = -1;
                      });
                    }
                  },
                ),
                Text('Value: $_counter'),
                IconButton(
                  icon: Icon(Icons.add),
                  onPressed: () {
                    if (!is_start) {
                      setState(() {
                        final newValue = _counter + 1;
                        _counter = newValue.clamp(1, 5);
                        int size = 1 << _counter;
                        matrix = List.generate(size + 1,
                            (_) => List.generate(size + 1, (index) => 0));
                        _px = min(_px, size);
                        _py = min(_py, size);
                        matrix[_px][_py] = -1;
                      });
                    }
                  },
                ),
              ],
            ),
            const SizedBox(
              height: 5,
            ),
            CustomPaint(
              painter: GirdPainter(_counter, matrix),
              size: Size(pm_size / 2, pm_size / 2),
            ),
            const SizedBox(
              height: 15,
            ),
            Column(
              children: [
                Text('初始覆盖位置'),
                Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        IconButton(
                          icon: Icon(Icons.remove),
                          onPressed: () {
                            if (!is_start) {
                              setState(() {
                                if (_px > 1) _px--;
                                int size = 1 << _counter;
                                matrix = List.generate(
                                    size + 1,
                                    (_) =>
                                        List.generate(size + 1, (index) => 0));
                                matrix[_px][_py] = -1;
                              });
                            }
                          },
                        ),
                        Text('X: $_px'),
                        IconButton(
                          icon: Icon(Icons.add),
                          onPressed: () {
                            if (!is_start) {
                              setState(() {
                                int size = 1 << _counter;
                                if (_px < size) _px++;
                                matrix = List.generate(
                                    size + 1,
                                    (_) =>
                                        List.generate(size + 1, (index) => 0));
                                matrix[_px][_py] = -1;
                              });
                            }
                          },
                        ),
                      ],
                    ),
                    SizedBox(
                      width: 30,
                    ),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        IconButton(
                          icon: Icon(Icons.remove),
                          onPressed: () {
                            if (!is_start) {
                              setState(() {
                                if (_py > 1) _py--;
                                int size = 1 << _counter;
                                matrix = List.generate(
                                    size + 1,
                                    (_) =>
                                        List.generate(size + 1, (index) => 0));
                                matrix[_px][_py] = -1;
                              });
                            }
                          },
                        ),
                        Text('Y: $_py'),
                        IconButton(
                          icon: Icon(Icons.add),
                          onPressed: () {
                            if (!is_start) {
                              setState(() {
                                int size = 1 << _counter;
                                if (_py < size) _py++;
                                matrix = List.generate(
                                    size + 1,
                                    (_) =>
                                        List.generate(size + 1, (index) => 0));
                                matrix[_px][_py] = -1;
                              });
                            }
                          },
                        ),
                      ],
                    ),
                  ],
                ),
              ],
            ),
            IconButton(
                onPressed: () {
                  if (!is_start) {
                    _start();
                  }
                },
                icon: const Icon(Icons.play_arrow)),
          ],
        ),
      ),
    );
  }
}

class GirdPainter extends CustomPainter {
  int count;
  List<List<int>> matrix;
  GirdPainter(this.count, this.matrix);
  @override
  void paint(Canvas canvas, Size size) {
    double w = size.width / (1 << count);
    double h = size.height / (1 << count);
    Paint _paint = Paint()
      ..color = Colors.black
      ..style = PaintingStyle.stroke
      ..strokeWidth = w / 100;

    Paint _rectpaint = Paint()
      ..color = Colors.blue
      ..style = PaintingStyle.fill;

    Paint _keypaint = Paint()
      ..color = Colors.red
      ..style = PaintingStyle.fill;

    for (int i = 0; i < matrix.length - 1; i++) {
      for (int j = 0; j < matrix[i].length - 1; j++) {
        Rect rect = Rect.fromLTRB(
            w * j + 1.0, h * i + 1.0, w * (j + 1) - 1.0, h * (i + 1) - 1.0);
        // print(rect);
        if (matrix[i + 1][j + 1] == -1) {
          //障碍矩形
          canvas.drawRect(rect, _keypaint);
        } else if (matrix[i + 1][j + 1] != 0) {
          _rectpaint.color =
              cols[cols.length - 1 - (matrix[i + 1][j + 1] * 3 % cols.length)]!;
          //实心矩形
          canvas.drawRect(rect, _rectpaint);
        } else {
          //画空心矩形
          canvas.drawRect(rect, _paint);
        }
      }
    }
  }

  @override
  bool shouldRepaint(CustomPainter oldDelegate) {
    return true;
  }
}
