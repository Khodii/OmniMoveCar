package zweitesFenster;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import Utils.TextFieldPort;
import Utils.UIUtils;
import java.awt.Color;

public class ZweitesFenster extends JFrame{
	
	/**
	 * 
	 */
	
	private static final long serialVersionUID = 1L;

	
	ZweitesFenster(){
		
		
		JPanel mainPanel = getMainJPanel();
		
		addLogo(mainPanel);
		battery(mainPanel);
		speed(mainPanel);
		
		getContentPane().add(mainPanel, BorderLayout.SOUTH);
		
        pack();
        setVisible(true);
        toFront();

        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        setLocation(screenSize.width / 2 - getWidth() / 2, screenSize.height / 2 - getHeight() / 2);
        
	}
	
	
	private JPanel getMainJPanel() {
        setUndecorated(true);

        Dimension size = new Dimension(700, 600);

        JPanel panel1 = new JPanel();
        panel1.setSize(size);
        panel1.setPreferredSize(size);
        panel1.setBackground(UIUtils.COLOR_BACKGROUND);
        panel1.setLayout(null);
        
        TextFieldPort titel = new TextFieldPort();
        titel.setEnabled(false);
        titel.setEditable(false);
        titel.setHorizontalAlignment(SwingConstants.CENTER);
        //titel.setBorderColor(UIUtils.COLOR_INTERACTIVE);
        titel.setFont(new Font("Segoe UI", Font.PLAIN, 14));
        titel.setText("OmniMove Driving Experience");
        titel.setBounds(20, 25, 250, 45);
        panel1.add(titel);
        panel1.setFocusable(true);
        panel1.requestFocus();

        MouseAdapter ma = new MouseAdapter() {
            int lastX, lastY;

            @Override
            public void mousePressed(MouseEvent e) {
                lastX = e.getXOnScreen();
                lastY = e.getYOnScreen();
            }

            @Override
            public void mouseDragged(MouseEvent e) {
                int x = e.getXOnScreen();
                int y = e.getYOnScreen();
                setLocation(getLocationOnScreen().x + x - lastX, getLocationOnScreen().y + y - lastY);
                lastX = x;
                lastY = y;
            }
        };

        panel1.addMouseListener(ma);
        panel1.addMouseMotionListener(ma);

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        return panel1;
    }
	
	 	
    
	private void addLogo(JPanel panel1) {
        JLabel label1 = new JLabel();
        label1.setFocusable(false);
        label1.setVisible(true);
        label1.setBounds(201,94,320,369);
        Image robot = new ImageIcon(this.getClass().getResource("/robot2.png")).getImage();
        label1.setIcon(new ImageIcon(robot));
        panel1.add(label1);
    }
	
	
	private void battery(JPanel panel2) {
		int akkustand;
		akkustand = 50;
		
        JProgressBar battery_number = new JProgressBar();
        battery_number.setBackground(UIUtils.COLOR_BACKGROUND);
        battery_number.setForeground(UIUtils.COLOR_INTERACTIVE);
        battery_number.setEnabled(false);
        battery_number.setLocation(531, 47);
		battery_number.setMinimum(0);
		battery_number.setMaximum(100);
		battery_number.setFocusable(false);
		battery_number.setSize(133,45);
		battery_number.setString("Akkustand: "+akkustand+ "%");
		battery_number.setStringPainted(true);
		battery_number.setFont(new Font("Segoe UI", Font.PLAIN, 12));
		
		//default values
		battery_number.setValue(50);
		
		panel2.add(battery_number);
		
	}
	
	
	private void speed(JPanel panel3) {
		
		int kmh = 10;
		
		JPanel combination = new JPanel();
		combination.setSize(222, 101);
		combination.setVisible(true);
		combination.setBackground(UIUtils.COLOR_BACKGROUND);
		
		JLabel geschwindigkeit = new JLabel();
		geschwindigkeit.setHorizontalAlignment(SwingConstants.CENTER);
		geschwindigkeit.setText("Geschwindigkeit");
		geschwindigkeit.setFont(new Font("Segoe UI", Font.PLAIN, 12));
		geschwindigkeit.setFocusable(false);
		geschwindigkeit.setEnabled(false);
		
		JSlider speed = new JSlider(JSlider.HORIZONTAL, 0, 30, 0);
		speed.setSize(123, 35);
		speed.setBackground(UIUtils.COLOR_BACKGROUND);
        speed.setEnabled(false);
        speed.setFocusable(false);
        speed.setLocation(292,495);
        speed.setMajorTickSpacing(5);
        speed.setMinorTickSpacing(1);
        speed.setPaintTicks(true);
        speed.setPaintLabels(true);
		
		speed.setMaximum(30);
		speed.setMinimum(0);
		speed.setValue(kmh);
		
		JLabel geschwindigkeit2 = new JLabel();
		geschwindigkeit2.setHorizontalAlignment(SwingConstants.CENTER);
		geschwindigkeit2.setText("" +kmh+ "km/h");
		geschwindigkeit2.setVisible(true);
		geschwindigkeit2.setFont(new Font("Segoe UI", Font.PLAIN, 12));
		geschwindigkeit2.setFocusable(false);
		geschwindigkeit2.setEnabled(false);
		
		combination.setLayout(new BorderLayout());
		combination.add(geschwindigkeit, BorderLayout.NORTH);
		combination.add(speed,BorderLayout.CENTER);
		combination.add(geschwindigkeit2,BorderLayout.SOUTH);
		combination.setLocation(264,488);
		
		panel3.add(combination);
		
	}
	

}
