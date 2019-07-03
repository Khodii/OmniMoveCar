package components;

import javax.swing.SwingUtilities;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JComponent;

import java.awt.BorderLayout;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.border.EmptyBorder;

public class SpeedMeter extends JComponent {
    private int meterWidth = 10;

    private float speed = 0f;
    private boolean breaks = false;
    private boolean colorfade = false;

    private Color background = Color.LIGHT_GRAY;
    private Color border = Color.BLACK;
    private Color fill = Color.GREEN;
    private Color maxSpeedFill = Color.ORANGE;
    private Color breakfill = Color.RED;


    public void setSpeed(float speed) {
        this.speed = speed;
        repaint();
    }

    public void setBreaks(boolean breaks) {
        this.breaks = breaks;
        repaint();
    }

    public void setColorfade(boolean colorfade) {
        this.colorfade = colorfade;
    }

    public void setMaxSpeedFill(Color maxSpeedFill) {
        this.maxSpeedFill = maxSpeedFill;
    }

    public boolean isColorfade() {
        return colorfade;
    }

    public Color getMaxSpeedFill() {
        return maxSpeedFill;
    }

    public void toggleBreaks() {
        setBreaks(!breaks);
    }

    public void setMeterWidth(int meterWidth) {
        this.meterWidth = meterWidth;
    }

    public void setBackgroundFill(Color background) {
        this.background = background;
        repaint();
    }

    public void setBorderFill(Color border) {
        this.border = border;
        repaint();
    }

    public void setFill(Color fill) {
        this.fill = fill;
        repaint();
    }

    public void setBreakfill(Color breakfill) {
        this.breakfill = breakfill;
        repaint();
    }

    public Color getBackgroundFill() {
        return background;
    }

    public Color getBorderFIll() {
        return border;
    }

    public Color getFill() {
        return fill;
    }

    public Color getBreakfill() {
        return breakfill;
    }

    @Override
    protected void paintComponent(Graphics g) {
        int w = Math.min(meterWidth, getWidth());
        int h = getHeight();
        int x = getWidth() / 2 - w / 2;
        int y = 0;

        g.setColor(background);
        g.fillRect(x, y, w, h);

        g.setColor(border);
        g.drawRect(x, y, w - 1, h - 1);

        int a = Math.round(speed * (h - 2));
        if (colorfade)
            g.setColor(new Color(Math.min(fill.getRed() + Math.round((maxSpeedFill.getRed() - fill.getRed()) * (Math.abs(speed))),255),
                    Math.min(fill.getGreen() + Math.round((maxSpeedFill.getGreen() - fill.getGreen()) * (Math.abs(speed))),255),
                    Math.min(fill.getBlue() + Math.round((maxSpeedFill.getBlue() - fill.getBlue()) * (Math.abs(speed))),255),
                    Math.min(fill.getAlpha() + Math.round((maxSpeedFill.getAlpha() - fill.getAlpha()) * (Math.abs(speed))),255)));
        else
            g.setColor(fill);
        if (a > 0)
            g.fillRect(x + 1, y + h / 2 - a / 2, w - 2, a / 2);
        else
            g.fillRect(x + 1, y + h / 2 - 1, w - 2, -(a / 2) + 1);

        int p = Math.round(h / 2);
        g.setColor(breakfill);
        g.drawLine(x + 1, y + h - 1 - p, x + w - 1, y + h - 1 - p);

        if (breaks) {
            g.setColor(breakfill);
            g.fillRect(x + 1, y + 1, w - 2, h / 6);
            g.fillRect(x + 1, y + h - 1 - h / 6, w - 2, h / 6);
        }
    }

    @Override
    public Dimension getMinimumSize() {
        Dimension min = super.getMinimumSize();
        if (min.width < meterWidth)
            min.width = meterWidth;
        if (min.height < meterWidth)
            min.height = meterWidth;
        return min;
    }

    @Override
    public Dimension getPreferredSize() {
        Dimension pref = super.getPreferredSize();
        pref.width = meterWidth;
        return pref;
    }

    @Override
    public void setPreferredSize(Dimension pref) {
        super.setPreferredSize(pref);
        setMeterWidth(pref.width);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Meter");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            JPanel content = new JPanel(new BorderLayout());
            content.setBorder(new EmptyBorder(25, 50, 25, 50));

            SpeedMeter meter = new SpeedMeter();
            meter.setPreferredSize(new Dimension(9, 100));
            content.add(meter, BorderLayout.CENTER);

            frame.setContentPane(content);
            frame.pack();
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);

            new Thread(new SpeedTester(meter)).start();
        });
    }

    static class SpeedTester implements Runnable {
        final SpeedMeter meter;

        SpeedTester(final SpeedMeter meter) {
            this.meter = meter;
        }

        @Override
        public void run() {
            meter.setColorfade(true);
            float speed = 0;
            while (true) {
                if (speed > 1) {
                    speed = -1;
                    meter.toggleBreaks();
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } else
                    speed += 0.01;
                meter.setSpeed(speed);
                meter.setBreaks(false);
                try {
                    Thread.sleep(20);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}