//
//  ofxiSocial.h
//
//  Created by ISHII 2bit on 2013/12/02.
//
//

#ifndef __ofxiSocial__
#define __ofxiSocial__

#import <Social/Social.h>
#include "ofMain.h"
#import "ofxObjective-C++Utility.h"

typedef enum {
    ofxiSocialServiceTypeTwitter,
    ofxiSocialServiceTypeFacebook,
    
} ofxiSocialServiceType;

class ofxiSocial {
public:
    static void share(ofxiSocialServiceType type, string text, ofImage &image) {
        ofxiSocial::share(type, text, "", image);
    }
    static void share(ofxiSocialServiceType type, string text, string url, ofImage &image) {
        NSString *serviceType = nil;
        switch(type) {
            case ofxiSocialServiceTypeTwitter:
                serviceType = SLServiceTypeTwitter;
                break;
            case ofxiSocialServiceTypeFacebook:
                serviceType = SLServiceTypeFacebook;
                break;
            default:
                break;
        }
        if(serviceType == nil) {
            ofLogError() << "Service Type is invalid.";
            return;
        }
        SLComposeViewController *controller = [SLComposeViewController composeViewControllerForServiceType:serviceType];
        
        [controller setInitialText:convert(text)];
        [controller addImage:[UIImage imageWithCGImage:convert(image)]];
        [controller addURL:[NSURL URLWithString:convert(url)]];
        [controller setCompletionHandler:^(SLComposeViewControllerResult result) {
            
        }];
        [[[[UIApplication sharedApplication] keyWindow] rootViewController] presentViewController:controller
                                                                    animated:YES
                                                                  completion:nil];
    }
    
    static void share(ofxiSocialServiceType type, string text, string url = "") {
        NSString *serviceType = nil;
        switch(type) {
            case ofxiSocialServiceTypeTwitter:
                serviceType = SLServiceTypeTwitter;
                break;
            case ofxiSocialServiceTypeFacebook:
                serviceType = SLServiceTypeFacebook;
                break;
            default:
                break;
        }
        if(serviceType == nil) {
            ofLogError() << "Service Type is invalid.";
            return;
        }
        SLComposeViewController *controller = [SLComposeViewController composeViewControllerForServiceType:serviceType];
        [controller setInitialText:convert(text)];
        
        if(url != "") [controller addURL:[NSURL URLWithString:convert(url)]];
        [controller setCompletionHandler:^(SLComposeViewControllerResult result) {
            
        }];
        [[[[UIApplication sharedApplication] keyWindow] rootViewController] presentViewController:controller
                                                                                         animated:YES
                                                                                       completion:nil];
    }
private:
};

#endif /* defined(__ofxiSocial__) */
