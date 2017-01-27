package com.company;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedImage img = null;
        try {
            img = ImageIO.read(new File("C:\\Users\\callum\\Desktop\\rock.png"));
        } catch (IOException e) {
        }

        int w = img.getWidth();
        int h = img.getHeight();

        byte[] fileBuff = new byte[8+(3*w*h)];

        byte[] width = new byte[4];
        byte[] height = new byte[4];
        width =  ByteBuffer.allocate(4).putInt(w).array();
        height =  ByteBuffer.allocate(4).putInt(h).array();

        fileBuff[0] = width[0]; fileBuff[1] = width[1]; fileBuff[2] = width[2]; fileBuff[3] = width[3];
        fileBuff[4] = height[0]; fileBuff[5] = height[1]; fileBuff[6] = height[2]; fileBuff[7] = height[3];

        int pos = 0;
        for (int y = 0; y < h; y++){
            for (int x = 0; x < w; x++){
                int rgb = img.getRGB(x,y);
                fileBuff[8+pos+2] = (byte) ((rgb & 0x00ff0000) >> 16);
                fileBuff[8+pos+1] = (byte) ((rgb & 0x0000ff00) >> 8);
                fileBuff[8+pos+0] = (byte) (rgb & 0x000000ff);
                pos+=3;
            }
        }
        FileOutputStream fos = new FileOutputStream("C:\\Users\\callum\\Desktop\\rock.bin");
        fos.write(fileBuff);
        fos.close();
    }
}
