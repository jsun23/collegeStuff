package hw5;

//read_wav.java     read_wav  ok.wav
//reads bytes one at a time as an int
/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW5
 * Date: 6/23/2015
 */
import java.io.*;

public class read_wav {
  char riff[] = new char[4];
  int sread, swrite;
  int fsize;
  char wave[] = new char[4];
  char fmt[] = new char[4];
  int nbytes;
  short ccode;
  short channels;
  int rate;
  int avgrate;
  short blockalign;
  short bps; // bits per sample
  char data[] = new char[4];
  int csize[] = new int[50]; // max 50 chunks
  int ncsize = 0;
  int ibyte; // byte of cound
  char more[] = new char[4];
  int smin = 0;
  int smax = 0;
  int savg;
  int nbread; // number of bytes read
  int outix; // number of output samples
  int A[]; // output sound amplitude, bigger than outix

  public read_wav(String file_in, String file_out, boolean ifwrite) {
	wav_read(file_in);
	if (ifwrite)
	    wav_write(file_out);
  }

  void wav_read(String inp) {
	System.out.println("read_wav running,  reading " + inp);
	outix = 0;

	try {
	    FileInputStream ds = new FileInputStream(inp);

	    sread = 4;
	    for (int i = 0; i < sread; i++)
		riff[i] = (char) ds.read();
	    System.out.println("read " + sread + " bytes, should be 4");
	    System.out.println("first 4 bytes should be RIFF " + riff[0]
			       + riff[1] + riff[2] + riff[3]);

	    fsize = 0;
	    smax = 1;
	    for (int i = 0; i < 4; i++) {
		fsize += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("file has " + fsize + " +8 bytes");

	    for (int i = 0; i < 4; i++)
		wave[i] = (char) ds.read();
	    System.out.println("4 bytes should be WAVE " + wave[0] + wave[1]
			       + wave[2] + wave[3]);

	    for (int i = 0; i < 4; i++)
		fmt[i] = (char) ds.read();
	    System.out.println("4 bytes should be fmt  " + fmt[0] + fmt[1]
			       + fmt[2] + fmt[3]);

	    nbytes = 0;
	    smax = 1;
	    for (int i = 0; i < 4; i++) {
		nbytes += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("block has " + nbytes + " bytes");

	    ccode = 0;
	    smax = 1;
	    for (int i = 0; i < 2; i++) {
		ccode += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("compression code = " + ccode);

	    channels = 0;
	    smax = 1;
	    for (int i = 0; i < 2; i++) {
		channels += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("channels = " + channels);

	    rate = 0;
	    smax = 1;
	    for (int i = 0; i < 4; i++) {
		rate += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("rate = " + rate);

	    avgrate = 0;
	    smax = 1;
	    for (int i = 0; i < 4; i++) {
		avgrate += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("avg rate = " + avgrate);

	    blockalign = 0;
	    smax = 1;
	    for (int i = 0; i < 2; i++) {
		blockalign += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("blockalign = " + blockalign);

	    bps = 0;
	    smax = 1;
	    for (int i = 0; i < 2; i++) {
		bps += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("bits per sample = " + bps);

	    for (int i = 0; i < 4; i++)
		data[i] = (char) ds.read();
	    System.out.println("4 bytes should be data " + data[0] + data[1]
			       + data[2] + data[3]);

	    csize[ncsize] = 0;
	    smax = 1;
	    for (int i = 0; i < 4; i++) {
		csize[ncsize] += ds.read() * smax;
		smax *= 256;
	    }
	    System.out.println("chunk has " + csize[ncsize] + " bytes");

	    nbread = 44;
	    System.out.println(nbread + " bytes read so far");
	    A = new int[fsize + 8 - nbread]; // -8 +8 below thus big enough
	    outix = 0;

	    savg = 0;
	    for (int i = 0; i < csize[ncsize]; i++) {
		ibyte = ds.read(); // signed byte
		if (ibyte > 127)
		    ibyte = ibyte - 256;
		A[outix] = ibyte;
		outix++;
		savg = savg + ibyte;
		if (i == 0) {
		    smin = ibyte;
		    smax = ibyte;
		}
		smin = ibyte < smin ? ibyte : smin;
		smax = ibyte > smax ? ibyte : smax;
		if (i < 10 || i > csize[ncsize] - 10)
		    System.out.println("sound byte =" + ibyte);
	    }
	    savg = savg / csize[ncsize];
	    System.out.println("smin=" + smin + ", smax=" + smax + ", savg="
			       + savg);

	    nbread = nbread + csize[ncsize];
	    System.out.println(nbread + " bytes read so far");

	    // read rest of chunks
	    while (nbread + 17 < fsize) {
		ncsize++;
		for (int i = 0; i < 4; i++)
		    more[i] = (char) ds.read();
		System.out.println("4 bytes should be WAVE " + more[0]
				   + more[1] + more[2] + more[3]);

		csize[ncsize] = 0;
		smax = 1;
		for (int i = 0; i < 4; i++) {
		    csize[ncsize] += ds.read() * smax;
		    smax *= 256;
		}
		System.out.println("chunk has " + csize[ncsize] + " bytes");

		for (int i = 0; i < csize[ncsize]; i++) {
		    ibyte = ds.read(); // signed byte
		    if (ibyte > 127)
			ibyte = ibyte - 256;
		    A[outix] = ibyte;
		    outix++;
		}
		nbread = nbread + 8 + csize[ncsize];
		System.out.println(nbread + " bytes read so far");
	    }
	    ds.close();
	} catch (Exception e) {
	    System.out.println("wav_read, some exception thrown");
	}
	System.out.println("end wav_read");
  } // end wav_read

  void wav_write(String outp) {
	System.out.println("read_write running,  writing " + outp);
	int inix = 0;

	ncsize = 0;
	try {
	    FileOutputStream ds = new FileOutputStream(outp);

	    sread = 4;
	    for (int i = 0; i < sread; i++)
		ds.write(riff[i]);
	    System.out.println("wrote " + sread + " bytes, should be 4");
	    System.out.println("wrote first 4 bytes should be RIFF " + riff[0]
			       + riff[1] + riff[2] + riff[3]);

	    smax = fsize;
	    for (int i = 0; i < 4; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote file has " + fsize + " +8 bytes");

	    for (int i = 0; i < 4; i++)
		ds.write(wave[i]);
	    System.out.println("wrote 4 bytes should be WAVE " + wave[0]
			       + wave[1] + wave[2] + wave[3]);

	    for (int i = 0; i < 4; i++)
		ds.write(fmt[i]);
	    System.out.println("wrote 4 bytes should be fmt  " + fmt[0]
			       + fmt[1] + fmt[2] + fmt[3]);

	    smax = nbytes;
	    for (int i = 0; i < 4; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote block has " + nbytes + " bytes");

	    smax = ccode;
	    for (int i = 0; i < 2; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote compression code = " + ccode);

	    smax = channels;
	    for (int i = 0; i < 2; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote channels = " + channels);

	    smax = rate;
	    for (int i = 0; i < 4; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote rate = " + rate);

	    smax = avgrate;
	    for (int i = 0; i < 4; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote avg rate = " + avgrate);

	    smax = blockalign;
	    for (int i = 0; i < 2; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote blockalign = " + blockalign);

	    smax = bps;
	    for (int i = 0; i < 2; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote bits per sample = " + bps);

	    for (int i = 0; i < 4; i++)
		ds.write(data[i]);
	    System.out.println("wrote 4 bytes should be data " + data[0]
			       + data[1] + data[2] + data[3]);

	    smax = csize[ncsize];
	    for (int i = 0; i < 4; i++) {
		ds.write(smax % 256);
		smax /= 256;
	    }
	    System.out.println("wrote chunk has " + csize[ncsize] + " bytes");

	    nbread = 44;
	    System.out.println(nbread + " bytes written so far");

	    savg = 0;
	    for (int i = 0; i < csize[ncsize]; i++) {
		ibyte = A[inix];
		inix++;
		if (ibyte < 0)
		    ibyte = ibyte + 256;
		ds.write(ibyte); // signed byte
		if (inix >= outix)
		    break;
	    }

	    nbread = nbread + csize[ncsize];
	    System.out.println(nbread + " bytes written so far");

	    // write rest of chunks
	    while (nbread + 17 < fsize) {
		ncsize++;
		if (inix >= outix)
		    break;
		for (int i = 0; i < 4; i++)
		    ds.write(more[i]);
		System.out.println("wrote 4 bytes should be WAVE " + more[0]
				   + more[1] + more[2] + more[3]);

		smax = csize[ncsize];
		for (int i = 0; i < 4; i++) {
		    ds.write(smax % 256);
		    smax /= 256;
		}
		System.out.println("wrote chunk has " + csize[ncsize]
				   + " bytes");

		for (int i = 0; i < csize[ncsize]; i++) {
		    ibyte = A[inix];
		    inix++;
		    if (ibyte < 0)
			ibyte = ibyte + 256;
		    ds.write(ibyte); // signed byte
		    if (inix >= outix)
			break;
		}
		nbread = nbread + 8 + csize[ncsize];
		System.out.println(nbread + " bytes written so far");
	    }
	    // ds.write(0); // on some files
	    ds.close();
	} catch (Exception e) {
	    System.out.println("wav_write, some exception thrown");
	}
	System.out.println("end wav_write");
  } // end wav_write

  public static void main(String[] args) {
	String file_in = "trainf.wav";
	if (args.length > 0) {
	    file_in = args[0];
	}
	String file_out = "junk.wav";
	if (args.length > 1) {
	    file_out = args[1];
	}
	new read_wav(file_in, file_out, true);
  } // end main
} // end class read_wav of read_wav.java

