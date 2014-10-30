//
//  GPDLoginViewController.m
//  GPShopper-iOS
//
//  Created by Matthew Reed on 10/28/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDLoginViewController.h"
#import "GPDRegistrationViewController.h"

@interface GPDLoginViewController ()


@property (strong, nonatomic) SCRegistrationState *state;
@property (strong, nonatomic) SCProfile *profile;
@property (strong, nonatomic) SCSession *session;

@property (strong, nonatomic) IBOutlet UITextField *usernameTextField;
@property (strong, nonatomic) IBOutlet UITextField *passwordTextField;

@property (strong, nonatomic) IBOutlet UIBarButtonItem *cancelButton;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *spinner;

@end

@implementation GPDLoginViewController
@synthesize state;
@synthesize session;
@synthesize profile;

@synthesize usernameTextField;
@synthesize passwordTextField;
@synthesize spinner;

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        state = [SCRegistrationState defaultState];
        profile = [SCProfile defaultProfile];
        session = [SCSession defaultSession];
    }
    return self;
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    self.navigationItem.leftBarButtonItem = self.cancelButton;
    self.title = @"Login";
    
    [state addObserver:self forKeyPath:@"status" options:0 context:nil];
    [profile addObserver:self forKeyPath:@"fetchStatus" options:0 context:nil];
    [profile addObserver:self forKeyPath:@"updateStatus" options:0 context:nil];
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center addObserverForName:@"scsession_updated" object:session queue:nil usingBlock:^(NSNotification *note) {
        if (session.exists) {
            [profile fetch];
        } else if (session.createFailed) {
            
        } else if (session.destroyFailed) {
            
        }
    }];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)cancelButtonPressed:(id)sender {
    [state clear];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)loginButtonPressed:(id)sender {
    NSRegularExpression *regex = [[NSRegularExpression alloc] initWithPattern:@"^[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$" options:(NSRegularExpressionCaseInsensitive) error:nil];
    NSTextCheckingResult *match = [regex firstMatchInString:usernameTextField.text options:0 range:NSMakeRange(0, [usernameTextField.text length])];
    
    if  ([usernameTextField.text isEqualToString:@""] || [passwordTextField.text isEqualToString:@""]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"You must enter an email and password" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    } else if (!match) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Please enter a valid email." delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    } else {
        spinner.hidden = NO;
        [state loginWithIdentifier:usernameTextField.text zipcode:@""];
    }
}

- (IBAction)createAccountButtonPressed:(id)sender {
    GPDRegistrationViewController *vc = [[GPDRegistrationViewController alloc] initWithNibName:@"GPDRegistrationViewController" bundle:nil];
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"status"]) {
        switch (state.status) {
            case SCRegStatusUnregistered:
                
                break;
            case SCRegStatusBusy:
                
                break;
            case SCRegStatusFail:
                
                break;
            case SCRegStatusSuccess:
                [self login];
                break;
        }
    } else if ([keyPath isEqualToString:@"fetchStatus"]) {
        switch (profile.fetchStatus) {
            case SCProfileRemoteBusy:
                
                break;
            case SCProfileRemoteFail:
                
                break;
            case SCProfileRemoteNone:
                
                break;
            case SCProfileRemoteSuccess:
                [self performSelectorOnMainThread:@selector(checkPassword) withObject:nil waitUntilDone:NO];
                break;
        }
    }
}

- (void)login {
    [session create];
    
}

- (void)checkPassword {
    spinner.hidden = YES;
    if (![passwordTextField.text isEqualToString:[profile.supplemental objectForKey:@"password"]]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Email or password incorrect" delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
        [alert show];
    } else {
        [self dismissViewControllerAnimated:YES completion:nil];
    }
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
