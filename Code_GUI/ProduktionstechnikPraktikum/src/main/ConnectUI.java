package main;
import Toaster.Toaster;
import Utils.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ConnectUI extends JFrame {

    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private final Toaster toaster;

    public static void main(String[] args) {
        new ConnectUI();
    }

    private ConnectUI() {
        JPanel mainJPanel = getMainJPanel();

        addLogo(mainJPanel);

        addSeparator(mainJPanel);

        addIPTextField(mainJPanel);

        addPortTextField(mainJPanel);

        addConnectButton(mainJPanel);

        getContentPane().add(mainJPanel);

        pack();
        setVisible(true);
        toFront();

        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        setLocation(screenSize.width / 2 - getWidth() / 2, screenSize.height / 2 - getHeight() / 2);

        toaster = new Toaster(mainJPanel);
    }

    private JPanel getMainJPanel() {
        setUndecorated(true);

        Dimension size = new Dimension(800, 400);

        JPanel panel1 = new JPanel();
        panel1.setSize(size);
        panel1.setPreferredSize(size);
        panel1.setBackground(UIUtils.COLOR_BACKGROUND);
        panel1.setLayout(null);
        
        TextFieldPort titel = new TextFieldPort();
        titel.setEnabled(false);
        titel.setEditable(false);
        titel.setHorizontalAlignment(SwingConstants.CENTER);
        titel.setBorderColor(UIUtils.COLOR_INTERACTIVE);
        titel.setFont(new Font("Segoe UI", Font.PLAIN, 16));
        titel.setText("OmniMove Wlan Verbindung");
        titel.setBounds(68, 57, 250, 44);
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

    private void addSeparator(JPanel panel1) {
        JSeparator separator1 = new JSeparator();
        separator1.setOrientation(SwingConstants.VERTICAL);
        separator1.setForeground(UIUtils.COLOR_OUTLINE);
        panel1.add(separator1);
        separator1.setBounds(387, 41, 2, 316);
    }

    private void addLogo(JPanel panel1) {
        JLabel label1 = new JLabel();
        //label1.setSize(300,300);
        label1.setFocusable(false);
        label1.setBounds(57, 123, 273, 197);
        //ImageIcon robot = new ImageIcon(new ImageIcon("/robot.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT));
        //label1.setIcon(robot);
        Image robot = new ImageIcon(this.getClass().getResource("/robot.png")).getImage();
        label1.setIcon(new ImageIcon(robot));
        panel1.add(label1);
    }

    private void addIPTextField(JPanel panel1) {
        TextFieldPort usernameField = new TextFieldPort();
        //usernameField.setBorderColor(new Color(102, 205, 170));

        usernameField.setText(UIUtils.PLACEHOLDER_TEXT_IP);
        usernameField.setForeground(UIUtils.COLOR_OUTLINE);
        usernameField.setBorderColor(UIUtils.COLOR_OUTLINE);

        usernameField.setBounds(473, 109, 250, 44);
        usernameField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
                if (usernameField.getText().equals(UIUtils.PLACEHOLDER_TEXT_IP)) {
                    usernameField.setText("");
                }
                usernameField.setForeground(Color.white);
                usernameField.setBorderColor(UIUtils.COLOR_INTERACTIVE);
            }

            @Override
            public void focusLost(FocusEvent e) {
                if (usernameField.getText().isEmpty()) {
                    usernameField.setText(UIUtils.PLACEHOLDER_TEXT_IP);
                }
                usernameField.setForeground(UIUtils.COLOR_OUTLINE);
                usernameField.setBorderColor(UIUtils.COLOR_OUTLINE);
            }
        });

        panel1.add(usernameField);
    }

    private void addPortTextField(JPanel panel1) {
        TextFieldIP passwordField = new TextFieldIP();
        //passwordField.setBorderColor(new Color(102, 205, 170));

        passwordField.setText(UIUtils.PLACEHOLDER_TEXT_PORT);
        passwordField.setForeground(UIUtils.COLOR_OUTLINE);
        passwordField.setBorderColor(UIUtils.COLOR_OUTLINE);

        passwordField.setBounds(473, 168, 250, 44);
        passwordField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
            	if (passwordField.getText().equals(UIUtils.PLACEHOLDER_TEXT_PORT)) {
                    passwordField.setText("");
                }
                passwordField.setForeground(Color.white);
                passwordField.setBorderColor(UIUtils.COLOR_INTERACTIVE);
            }

            @Override
            public void focusLost(FocusEvent e) {
            	if (passwordField.getText().isEmpty()) {
                    passwordField.setText(UIUtils.PLACEHOLDER_TEXT_PORT);
                }
                passwordField.setForeground(UIUtils.COLOR_OUTLINE);
                passwordField.setBorderColor(UIUtils.COLOR_OUTLINE);
            }
        });

        passwordField.addKeyListener(new KeyAdapter() {
            @Override
            public void keyTyped(KeyEvent e) {
                if (e.getKeyChar() == KeyEvent.VK_ENTER)
                    loginEventHandler();
            }
        });

        panel1.add(passwordField);
    }

    private void addConnectButton(JPanel panel1) {
        final Color[] connectColors = {UIUtils.COLOR_INTERACTIVE, Color.white};

        JLabel connectButton = new JLabel() {
            /**
			 * 
			 */
			private static final long serialVersionUID = 1L;

			@Override
            protected void paintComponent(Graphics g) {
                Graphics2D g2 = UIUtils.get2dGraphics(g);
                super.paintComponent(g2);

                Insets insets = getInsets();
                int w = getWidth() - insets.left - insets.right;
                int h = getHeight() - insets.top - insets.bottom;
                g2.setColor(connectColors[0]);
                g2.fillRoundRect(insets.left, insets.top, w, h, UIUtils.ROUNDNESS, UIUtils.ROUNDNESS);

                FontMetrics metrics = g2.getFontMetrics(UIUtils.FONT_GENERAL_UI);
                int x2 = (getWidth() - metrics.stringWidth(UIUtils.BUTTON_TEXT_CONNECT)) / 2;
                int y2 = ((getHeight() - metrics.getHeight()) / 2) + metrics.getAscent();
                g2.setFont(UIUtils.FONT_GENERAL_UI);
                g2.setColor(connectColors[1]);
                g2.drawString(UIUtils.BUTTON_TEXT_CONNECT, x2, y2);
            }
        };

        connectButton.addMouseListener(new MouseAdapter() {

            @Override
            public void mousePressed(MouseEvent e) {
                loginEventHandler();
            }

            @Override
            public void mouseEntered(MouseEvent e) {
                connectColors[0] = UIUtils.COLOR_INTERACTIVE_DARKER;
                connectColors[1] = UIUtils.OFFWHITE;
                connectButton.repaint();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                connectColors[0] = UIUtils.COLOR_INTERACTIVE;
                connectColors[1] = Color.white;
                connectButton.repaint();
            }
        });

        connectButton.setBackground(UIUtils.COLOR_BACKGROUND);
        connectButton.setBounds(473, 247, 250, 44);
        connectButton.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        panel1.add(connectButton);
    }

    private void loginEventHandler() {
    	// hier Connect Code reinschreiben
        toaster.warn("Login event");
    }
}